#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tester.h"
#include "timing.h"


int run_timed_test(struct timed_test *t)
{
	struct timespec tic, toc;
	void *output = NULL;

	t->status = STATUS_BUSY;

	output = malloc(t->elem_size * t->data_size);

	if (t->defs.test_name.name == NULL || t->defs.test_name.type == NULL
			|| t->defs.fp == NULL || t->input == NULL || output == NULL
			|| t->expected == NULL || t->elem_size == 0) {
		t->status = STATUS_DONE;
		t->result = -RESULT_INVALID_PARAM;
		return t->result;
	}

	fprintf(stderr, "Initialising test: %s %s %s %s\n",
		t->defs.test_name.name, t->defs.test_name.type,
		t->defs.test_name.details, t->input_descr);

	t->defs.clear_counters();

#ifdef DBGPRINT
	fprintf(stderr, "\nBefore initialisation: %s %s %s %s\n",
		t->defs.test_name.name, t->defs.test_name.type,
		t->defs.test_name.details, t->input_descr);

	for (size_t i = 0; i < t->data_size / t->elem_size; i++)
		fprintf(stderr, "input[%zu]=%d\toutput[%zu]=%d\texpected[%zu]=%d\n",
				i, t->input[i], i, ((int*) output)[i], i,
				t->expected[i]);
#endif

	memcpy(output, t->input, t->data_size);

#ifdef DBGPRINT
	fprintf(stderr, "\nAfter initialisation: %s %s %s %s\n",
		t->defs.test_name.name, t->defs.test_name.type,
		t->defs.test_name.details, t->input_descr);

	for (size_t i = 0; i < t->data_size / t->elem_size; i++)
		fprintf(stderr, "input[%zu]=%d\toutput[%zu]=%d\texpected[%zu]=%d\n",
				i, t->input[i], i, ((int*) output)[i], i,
				t->expected[i]);
#endif
	fprintf(stderr, "Starting test: %s %s %s %s\n",
		t->defs.test_name.name, t->defs.test_name.type,
		t->defs.test_name.details, t->input_descr);

	clock_gettime(CLOCK_MONOTONIC, &tic);
	t->defs.fp(output, t->input_l, t->input_r);
	clock_gettime(CLOCK_MONOTONIC, &toc);

	timespec_diff(&toc, &tic, &t->time);

	if (!memcmp(t->expected, output, t->data_size))
		t->result = RESULT_SUCCESS;
	else
		t->result = -RESULT_MISMATCH;

	t->cntrs = t->defs.get_counters();

#ifdef DBGPRINT
	fprintf(stderr, "\nResult: %s %s %s %s\n",
		t->defs.test_name.name, t->defs.test_name.type,
		t->defs.test_name.details, t->input_descr);

	for (size_t i = 0; i < t->data_size/t->elem_size; i++) {
		fprintf(stderr, "input[%zu]=%d\toutput[%zu]=%d\texpected[%zu]=%d",
			i, t->input[i], i, ((int*) output)[i], i, t->expected[i]);
		fprintf(stderr, " %s\n",
			memcmp(&t->expected[i], &((int*) output)[i], t->elem_size) ?
			"FAIL" : "");
	}
#endif
	free(output);
	output = NULL;

	t->status = STATUS_DONE;

	return t->result;
}

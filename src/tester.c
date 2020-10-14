#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tester.h"
#include "timing.h"

int build_timed_tests(struct timed_test *to_test, size_t to_test_len,
	struct timed_test_input *data, size_t data_len,
	struct timed_test **out, size_t *out_len)
{
	if (to_test == NULL || to_test_len == 0 || data == NULL || data_len == 0
			|| out == NULL || out_len == NULL) {
		return -BUILD_NO_MEM;
	}

	*out_len = to_test_len * data_len;
	*out = malloc(sizeof(**out) * (*out_len));
	if (*out == NULL)
		return -BUILD_NO_MEM;

	for (size_t i = 0, k = 0; i < to_test_len; i++) {
		for (size_t j = 0; j < data_len; j++, k++) {
			(*out)[k].defs = to_test[i].defs;
			(*out)[k].expected = to_test[i].expected;
			(*out)[k].data = data[j];
		}
	}

#ifdef DBGPRINT
	printf("Tests:\n");
	for (size_t i = 0; i < *out_len; i++)
		printf("%s %s %s %s\n",
		(*out)[i].defs.test_name.name, (*out)[i].defs.test_name.type,
		(*out)[i].defs.test_name.details, (*out)[i].data.descr);
#endif

	return BUILD_SUCCESS;
}

int run_timed_test(struct timed_test *t)
{
	struct timespec tic, toc;
	void *output = NULL;

	t->status = STATUS_BUSY;

	output = malloc(t->data.elem_size * t->data.data_size);

	if (t->defs.test_name.name == NULL || t->defs.test_name.type == NULL
			|| t->defs.fp == NULL || t->data.input == NULL || output == NULL
			|| t->expected == NULL || t->data.elem_size == 0
			|| t->data.data_size == 0) {
		t->status = STATUS_DONE;
		t->result = -RESULT_INVALID_PARAM;
		return t->result;
	}

	fprintf(stderr, "Initialising test: %s %s %s %s\n",
		t->defs.test_name.name, t->defs.test_name.type,
		t->defs.test_name.details, t->data.descr);

	t->defs.clear_counters();

#ifdef DBGPRINT
	fprintf(stderr, "\nBefore initialisation: %s %s %s %s\n",
		t->defs.test_name.name, t->defs.test_name.type,
		t->defs.test_name.details, t->data.descr);

	for (size_t i = 0; i < t->data.data_size / t->data.elem_size; i++)
		fprintf(stderr, "input[%zu]=%d\toutput[%zu]=%d\texpected[%zu]=%d\n",
				i, t->data.input[i], i, ((int*) output)[i], i,
				t->expected[i]);
#endif

	memcpy(output, t->data.input, t->data.data_size);

#ifdef DBGPRINT
	fprintf(stderr, "\nAfter initialisation: %s %s %s %s\n",
		t->defs.test_name.name, t->defs.test_name.type,
		t->defs.test_name.details, t->data.descr);

	for (size_t i = 0; i < t->data.data_size / t->data.elem_size; i++)
		fprintf(stderr, "input[%zu]=%d\toutput[%zu]=%d\texpected[%zu]=%d\n",
				i, t->data.input[i], i, ((int*) output)[i], i,
				t->expected[i]);
#endif
	fprintf(stderr, "Starting test: %s %s %s %s\n",
		t->defs.test_name.name, t->defs.test_name.type,
		t->defs.test_name.details, t->data.descr);

	clock_gettime(CLOCK_MONOTONIC, &tic);
	t->defs.fp(output, t->data.input_l, t->data.input_r);
	clock_gettime(CLOCK_MONOTONIC, &toc);

	timespec_diff(&toc, &tic, &t->time);

	if (!memcmp(t->expected, output, t->data.data_size))
		t->result = RESULT_SUCCESS;
	else
		t->result = -RESULT_MISMATCH;

	t->cntrs = t->defs.get_counters();

#ifdef DBGPRINT
	fprintf(stderr, "\nResult: %s %s %s %s\n",
		t->defs.test_name.name, t->defs.test_name.type,
		t->defs.test_name.details, t->data.descr);

	for (size_t i = 0; i < t->data.data_size / t->data.elem_size; i++) {
		fprintf(stderr, "input[%zu]=%d\toutput[%zu]=%d\texpected[%zu]=%d",
			i, t->data.input[i], i, ((int*) output)[i], i, t->expected[i]);
		fprintf(stderr, " %s\n",
			memcmp(&t->expected[i], &((int*) output)[i], t->data.elem_size) ?
			"FAIL" : "");
	}
#endif
	free(output);
	output = NULL;

	t->status = STATUS_DONE;

	return t->result;
}

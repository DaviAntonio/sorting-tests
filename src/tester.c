#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tester.h"
#include "timing.h"

int run_timed_test(struct timed_test *t)
{
	struct timespec tic, toc;
	void *output = NULL;

	fprintf(stderr, "Initialising test: %s\n", t->name);
	output = malloc(t->elem_size * t->data_size);

	if (t->name == NULL || t->fp == NULL || t->input == NULL ||
			output == NULL || t->expected == NULL ||
			t->elem_size == 0)
		return -1;

	t->clear_counters(t->fp);

#ifdef DBGPRINT
	fprintf(stderr, "\nBefore initialisation: %s\n", t->name);
	for (size_t i = 0; i < t->data_size / t->elem_size; i++)
		fprintf(stderr, "input[%zu]=%d\toutput[%zu]=%d\texpected[%zu]=%d\n",
				i, t->input[i], i, ((int*) output)[i], i,
				t->expected[i]);
#endif

	memcpy(output, t->input, t->data_size);

#ifdef DBGPRINT
	fprintf(stderr, "\nAfter initialisation: %s\n", t->name);
	for (size_t i = 0; i < t->data_size / t->elem_size; i++)
		fprintf(stderr, "input[%zu]=%d\toutput[%zu]=%d\texpected[%zu]=%d\n",
				i, t->input[i], i, ((int*) output)[i], i,
				t->expected[i]);
#endif

	fprintf(stderr, "Starting test: %s\n", t->name);
	clock_gettime(CLOCK_MONOTONIC, &tic);
	t->fp(output, t->input_l, t->input_r);
	clock_gettime(CLOCK_MONOTONIC, &toc);

	timespec_diff(&toc, &tic, &t->time);
	t->status = memcmp(t->expected, output, t->data_size);

	t->cntrs = t->get_counters(t->fp);

#ifdef DBGPRINT
	fprintf(stderr, "\nResult: %s\n", t->name);
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

	return 0;
}

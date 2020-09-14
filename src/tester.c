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

#ifdef DBGPRINT
	printf("\nBefore initialisation\n");
	for (size_t i = 0; i < t->data_size / t->elem_size; i++)
		printf("input[%lu]=%d\toutput[%lu]=%d\texpected[%lu]=%d\n",
				i, t->input[i], i, ((int*) output)[i], i,
				t->expected[i]);
#endif

	memcpy(output, t->input, t->data_size);

#ifdef DBGPRINT
	printf("\nAfter initialisation\n");
	for (size_t i = 0; i < t->data_size / t->elem_size; i++)
		printf("input[%lu]=%d\toutput[%lu]=%d\texpected[%lu]=%d\n",
				i, t->input[i], i, ((int*) output)[i], i,
				t->expected[i]);
#endif

	fprintf(stderr, "Starting test: %s\n", t->name);
	clock_gettime(CLOCK_MONOTONIC, &tic);
	t->fp(output, t->input_l, t->input_r);
	clock_gettime(CLOCK_MONOTONIC, &toc);

	timespec_diff(&toc, &tic, &t->time);
	t->status = memcmp(t->expected, output, t->data_size);

#ifdef DBGPRINT
	printf("\nResult\n");
	for (size_t i = 0; i < t->data_size/t->elem_size; i++)
		printf("input[%lu]=%d\toutput[%lu]=%d\texpected[%lu]=%d\n",
				i, t->input[i], i, ((int*) output)[i], i,
				t->expected[i]);
#endif
	free(output);
	output = NULL;

	return 0;
}

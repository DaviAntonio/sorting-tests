#ifndef TESTER_H
#define TESTER_H

#include <time.h>
#include "counters.h"

struct timed_test {
	char name[256];
	void (*fp)(void *, size_t, size_t);
	void (*clear_counters)(void (*)(void *, size_t, size_t));
	struct counters (*get_counters)(void (*)(void *, size_t, size_t));
	int *input;
	size_t input_l;
	size_t input_r;
	int *expected;
	size_t data_size;
	size_t elem_size;
	int status;
	struct timespec time;
	struct counters cntrs;
};

/**
 * Runs a test defined in a struct timed_test
 * The test is defined by its name, printed in the stderr
 * The function specified in a function pointer is executed using the data in
 * input and the arguments input_l, starting index on the array, and input_r,
 * last valid index of the array.
 * The function specified in clear_counters must clear the counter used by the
 * function pointed by fp.
 * The function pointed by the get_counters field must get the current counter
 * used by the function pointed by fp.
 * The data size is specified in data_size, and the size of each element, in
 * the elem_size field.
 * The results are registered internally in an array which is allocated and
 * freed after its evaluation.
 * The result of the difference between the expected data and the output is
 * recorded in the status field.
 * The execution time of the function if fp is recorded in the time struct
 * timespec.
 * The performance counters, number of swaps, comparisons and recursive calls
 * is recorded in cntrs' field struct.
 * Returns -1 if an invalid parameter is received or if the allocation of the
 * temporary output array fails, and 0 on success */
int run_timed_test(struct timed_test *t);

#endif

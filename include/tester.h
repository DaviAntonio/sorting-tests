#ifndef TESTER_H
#define TESTER_H

#include <time.h>

struct timed_test {
	char name[256];
	void (*fp)(void *v, size_t l, size_t r);
	int *input;
	size_t input_l;
	size_t input_r;
	int *output;
	int *expected;
	size_t data_size;
	size_t elem_size;
	int status;
	struct timespec time;
};

/**
 * Runs a test defined in a struct timed_test
 * The test is defined by its name, printed in the stderr
 * The function specified in a function pointer is executed using the data in
 * input and the arguments input_l, starting index on the array, and input_r,
 * last valid index of the array.
 * The data size is specified in data_size, and the size of each element, in
 * the elem_size field.
 * The results are recorded in the output, and the result of the difference
 * between the expected data and the output is recorded in the status field.
 * The execution time of the function if fp is recorded in the time struct
 * timespec.
 * Returns -1 if an invalid parameter is received, and 0 on success */
int run_timed_test(struct timed_test *t);

#endif

#ifndef TESTER_H
#define TESTER_H

#include "timed_test.h"

enum tester_build_tests_result {
	BUILD_SUCCESS,
	BUILD_INVALID_PARAM,
	BUILD_NO_MEM
};

/**
 * Generates an aray of timed_tests with each specifed input
 * The array returned is allocated on heap and must be freed
 * The size is recorded in the variable pointed by out_len
 * If any of the input lengths is 0, it will return with a failure
 * Return 0 on success
 */
int build_timed_tests(struct timed_test *to_test, size_t to_test_len,
	struct timed_test_input *data, size_t data_len,
	struct timed_test **out, size_t *out_len);

/**
 * Runs a test defined in a struct timed_test
 * Prints name in stderr
 * The results are registered internally in an array which is allocated and
 * freed after its evaluation.
 * Returns -1 if an invalid parameter is received or if the allocation of the
 * temporary output array fails, and 0 on success */
int run_timed_test(struct timed_test *t);

#endif

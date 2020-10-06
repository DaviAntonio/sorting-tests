#ifndef TESTER_H
#define TESTER_H

#include "timed_test.h"

/**
 * Runs a test defined in a struct timed_test
 * Prints name in stderr
 * The results are registered internally in an array which is allocated and
 * freed after its evaluation.
 * Returns -1 if an invalid parameter is received or if the allocation of the
 * temporary output array fails, and 0 on success */
int run_timed_test(struct timed_test *t);

#endif

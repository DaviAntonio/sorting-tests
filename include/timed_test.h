#ifndef TIMED_TEST_H
#define TIMED_TEST_H

#include <time.h>
#include "counters.h"

enum timed_test_result {
	RESULT_SUCCESS,
	RESULT_INVALID_PARAM,
	RESULT_MISMATCH
};

enum timed_test_status {
	STATUS_NOT_STARTED = -1,
	STATUS_BUSY = 0,
	STATUS_DONE = 1
};

struct timed_test_name {
	char name[64];
	char type[32];
	char details[160];
};

struct timed_test_defs {
	/** Details of #fp */
	struct timed_test_name test_name;
	/** Pointer to function that will be run with #input, #input_l, #input_r */
	void (*fp)(void *, size_t, size_t);
	/** Pointed function must clear counters used by #fp */
	void (*clear_counters)();
	/** Pointed function must get counters used by #fp */
	struct counters (*get_counters)();
};

struct timed_test {
	struct timed_test_defs defs;
	/** Input data description */
	char input_descr[32];
	/** Pointer to input data */
	int *input;
	/** Starting index of array pointed by #input */
	size_t input_l;
	/** Last valid index of array pointed by #input */
	size_t input_r;
	/** Pointer to expected result of #fp */
	int *expected;
	/** Size in bytes of #input #expected */
	size_t data_size;
	/** Size in bytes of each element of #input #expected */
	size_t elem_size;
	/** Result of the difference between the expected data and the output */
	int result;
	/** 1 when done, 0 when not started, less than zero while in progress */
	int status;
	/** Execution time of the function #fp */
	struct timespec time;
	/** Number of swaps, comparisons and recursive calls of #fp */
	struct counters cntrs;
};

#endif

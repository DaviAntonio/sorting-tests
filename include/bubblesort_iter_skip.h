#ifndef BUBBLESORT_ITER_SKIP
#define BUBBLESORT_ITER_SKIP

#include <stddef.h>
#include "counters.h"
#include "timed_test.h"

/* Gets timed test definitions */
struct timed_test_defs bubblesort_iter_skip_get_test_defs();

/* Clear the counters */
void bubblesort_iter_skip_clear_counters();

/* Get the counters */
struct counters bubblesort_iter_skip_get_counters();

/* Iterative optimised bubble sort on array [l, r]
 * Bubble sort will always place one or more elements in the correct place in
 * the array in each iteration. This implementation avoids the evaluation of
 * elements that were already sorted in their correct places */
void bubblesort_iter_skip(void *vin, size_t l, size_t r);

#endif

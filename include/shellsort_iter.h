#ifndef SHELLSORT_ITER_H
#define SHELLSORT_ITER_H

#include <stddef.h>
#include "counters.h"
#include "timed_test.h"

/* Gets timed test definitions */
struct timed_test_defs shellsort_iter_get_test_defs();

/* Clear the counters used by the fp function */
void shellsort_iter_clear_counters();

/* Get the counters used by the fp function */
struct counters shellsort_iter_get_counters();

/* Iterative shell sort on array [l, r]
 * h=1, h=3*h+1, h<=N/9  from Sedgewick's Algorithms in C */
void shellsort_iter(void *vin, size_t l, size_t r);

#endif

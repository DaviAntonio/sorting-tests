#ifndef SELECTIONSORT_ITER_H
#define SELECTIONSORT_ITER_H

#include <stddef.h>
#include "counters.h"
#include "timed_test.h"

/* Gets timed test definitions */
struct timed_test_defs selectionsort_iter_get_test_defs();

/* Clear the counters */
void selectionsort_iter_clear_counters();

/* Get the counters */
struct counters selectionsort_iter_get_counters();

/* Iterative selection sort on array [l, r] */
void selectionsort_iter(void *vin, size_t l, size_t r);

#endif

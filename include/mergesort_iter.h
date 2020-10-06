#ifndef MERGESORT_ITER_H
#define MERGESORT_ITER_H

#include <stddef.h>
#include "counters.h"
#include "timed_test.h"

/* Gets timed test definitions */
struct timed_test_defs mergesort_iter_get_test_defs();

/* Clear the counters */
void mergesort_iter_clear_counters();

/* Get the counters */
struct counters mergesort_iter_get_counters();

/* Iterative mergesort on array [l, r] */
void mergesort_iter(void *vin, size_t l, size_t r);

#endif

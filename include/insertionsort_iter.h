#ifndef INSERTIONSORT_ITER_H
#define INSERTIONSORT_ITER_H

#include <stddef.h>
#include "counters.h"
#include "timed_test.h"

/* Gets timed test definitions */
struct timed_test_defs insertionsort_iter_get_test_defs();

/* Clear the counters */
void insertionsort_iter_clear_counters();

/* Get the counters */
struct counters insertionsort_iter_get_counters();

/* Add iterative insertion sort [l, r] */
void insertionsort_iter(void *vin, size_t l, size_t r);

#endif

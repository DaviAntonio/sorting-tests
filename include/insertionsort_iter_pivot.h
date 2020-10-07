#ifndef INSERTIONSORT_ITER_PIVOT_H
#define INSERTIONSORT_ITER_PIVOT_H

#include <stddef.h>
#include "counters.h"
#include "timed_test.h"

/* Gets timed test definitions */
struct timed_test_defs insertionsort_iter_pivot_get_test_defs();

/* Add iterative insertion sort with pivot [l, r] */
void insertionsort_iter_pivot(void *vin, size_t l, size_t r);

#endif

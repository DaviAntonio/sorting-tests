#ifndef BUBBLESORT_ITER
#define BUBBLESORT_ITER

#include <stddef.h>
#include "counters.h"
#include "timed_test.h"

/* Gets timed test definitions */
struct timed_test_defs bubblesort_iter_get_test_defs();

/* Iterative bubble sort on array [l, r] */
void bubblesort_iter(void *vin, size_t l, size_t r);

#endif

#ifndef INSERTION_SORT_H
#define INSERTION_SORT_H

#include <stddef.h>
#include "counters.h"

/* Clear the counters used by the fp function */
void insertion_clear_counters(void (*fp)(void *, size_t, size_t));

/* Get the counters used by the fp function */
struct counters insertion_get_counters(void (*fp)(void *, size_t, size_t));

/* Add iterative insertion sort [l, r] */
void insertion_sort(void *vin, size_t l, size_t r);

/* Add iterative insertion sort with pivot [l, r] */
void insertion_sort_pivot(void *vin, size_t l, size_t r);

#endif

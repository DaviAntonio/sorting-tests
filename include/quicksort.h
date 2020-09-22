#ifndef QUICKSORT_H
#define QUICKSORT_H

#include <stddef.h>
#include "counters.h"

/* Clear the counters used by the fp function */
void quick_clear_counters(void (*fp)(void *, size_t, size_t));

/* Get the counters used by the fp function */
struct counters quick_get_counters(void (*fp)(void *, size_t, size_t));

/* Simple quicksort on array [l, r] */
void quicksort(void *vin, size_t l, size_t r);

/* Median of 3 quicksort on array [l, r] */
void quicksort_median_3(void *vin, size_t l, size_t r);

/* Median of 3 quicksort with shortest tail optimisation on array [l, r] */
void quicksort_median_3_short(void *vin, size_t l, size_t r);

#endif

#ifndef QUICKSORT_REC_M3_SHORT_H
#define QUICKSORT_REC_M3_SHORT_H

#include <stddef.h>
#include "counters.h"
#include "timed_test.h"

/* Gets timed test definitions */
struct timed_test_defs quicksort_rec_m3_short_get_test_defs();

/* Median of 3 quicksort with shortest tail optimisation on array [l, r] */
void quicksort_rec_m3_short(void *vin, size_t l, size_t r);

#endif

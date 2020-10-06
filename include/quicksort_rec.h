#ifndef QUICKSORT_REC_H
#define QUICKSORT_REC_H

#include <stddef.h>
#include "counters.h"
#include "timed_test.h"

/* Gets timed test definitions */
struct timed_test_defs quicksort_rec_get_test_defs();

/* Clear the counters */
void quicksort_rec_clear_counters();

/* Get the counters */
struct counters quicksort_rec_get_counters();

/* Simple quicksort on array [l, r] */
void quicksort_rec(void *vin, size_t l, size_t r);

#endif

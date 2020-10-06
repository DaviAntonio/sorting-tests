#ifndef SELECTIONSORT_REC_H
#define SELECTIONSORT_REC_H

#include <stddef.h>
#include "counters.h"
#include "timed_test.h"

/* Gets timed test definitions */
struct timed_test_defs selectionsort_rec_get_test_defs();

/* Clear the counters */
void selectionsort_rec_clear_counters();

/* Get the counters */
struct counters selectionsort_rec_get_counters();

/* Recursive selection sort on array [l, r] */
void selectionsort_rec(void *vin, size_t l, size_t r);

#endif

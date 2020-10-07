#ifndef SELECTIONSORT_REC_H
#define SELECTIONSORT_REC_H

#include <stddef.h>
#include "counters.h"
#include "timed_test.h"

/* Gets timed test definitions */
struct timed_test_defs selectionsort_rec_get_test_defs();

/* Recursive selection sort on array [l, r] */
void selectionsort_rec(void *vin, size_t l, size_t r);

#endif

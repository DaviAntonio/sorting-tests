#ifndef MERGESORT_REC_H
#define MERGESORT_REC_H

#include <stddef.h>
#include "counters.h"
#include "timed_test.h"

/* Gets timed test definitions */
struct timed_test_defs mergesort_rec_get_test_defs();

/* Simple mergesort on array [l, r] */
void mergesort_rec(void *vin, size_t l, size_t r);

#endif

#ifndef MERGESORT_H
#define MERGESORT_H

#include <stddef.h>
#include "counters.h"

/* Clear the counters used by the fp function */
void merge_clear_counters(void (*fp)(void *, size_t, size_t));

/* Get the counters used by the fp function */
struct counters merge_get_counters(void (*fp)(void *, size_t, size_t));

/* Simple mergesort on array [l, r] */
void mergesort(void *vin, size_t l, size_t r);

#endif

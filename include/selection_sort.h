#ifndef SELECTION_SORT_H
#define SELECTION_SORT_H

#include <stddef.h>
#include "counters.h"

/* Clear the counters used by the fp function */
void selection_clear_counters(void (*fp)(void *, size_t, size_t));

/* Get the counters used by the fp function */
struct counters selection_get_counters(void (*fp)(void *, size_t, size_t));

/* Iterative selection sort on array [l, r] */
void selection_sort(void *vin, size_t l, size_t r);
/* Recursive selection sort on array [l, r] */
void selection_sort_rec(void *vin, size_t l, size_t r);

#endif

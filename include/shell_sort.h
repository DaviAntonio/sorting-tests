#ifndef SHELL_SORT_H
#define SHELL_SORT_H

#include <stddef.h>
#include "counters.h"

/* Clear the counters used by the fp function */
void shell_clear_counters(void (*fp)(void *, size_t, size_t));

/* Get the counters used by the fp function */
struct counters shell_get_counters(void (*fp)(void *, size_t, size_t));

/* Iterative shell sort on array [l, r]
 * h=1, h=3*h+1, h<=N/9  from Sedgewick's Algorithms in C */
void shell_sort(void *vin, size_t l, size_t r);

#endif

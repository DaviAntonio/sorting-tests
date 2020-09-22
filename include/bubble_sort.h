#ifndef BUBBLE_SORT_H
#define BUBBLE_SORT_H

#include <stddef.h>
#include "counters.h"

/* Clear the counters used by the fp function */
void bubble_clear_counters(void (*fp)(void *, size_t, size_t));

/* Get the counters used by the fp function */
struct counters bubble_get_counters(void (*fp)(void *, size_t, size_t));

/* Iterative bubble sort on array [l, r] */
void bubble_sort(void *vin, size_t l, size_t r);

/* Recursive bubble sort on array [l, r] */
void bubble_sort_rec(void *vin, size_t l, size_t r);

/* Iterative optimised bubble sort on array [l, r]
 * The nested for loops are replaced by one for one loop and a while loop with
 * a flag */
void bubble_sort_optim(void *vin, size_t l, size_t r);

/* Iterative optimised bubble sort on array [l, r]
 * Bubble sort will always place one or more elements in the correct place in
 * the array in each iteration. This implementation avoids the evaluation of
 * elements that were already sorted in their correct places */
void bubble_sort_optim2(void *vin, size_t l, size_t r);

#endif

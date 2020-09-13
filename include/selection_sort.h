#ifndef SELECTION_SORT_H
#define SELECTION_SORT_H

#include <stddef.h>

/* Iterative selection sort on array [l, r] */
void selection_sort(void *vin, size_t l, size_t r);
/* Recursive selection sort on array [l, r] */
void selection_sort_rec(void *vin, size_t l, size_t r);

#endif

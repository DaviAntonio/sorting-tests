#ifndef SHELL_SORT_H
#define SHELL_SORT_H

#include <stddef.h>

/* Iterative shell sort on array [l, r]
 * h=1, h=3*h+1, h<=N/9  from Sedgewick's Algorithms in C */
void shell_sort(void *vin, size_t l, size_t r);

#endif

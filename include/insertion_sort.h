#ifndef INSERTION_SORT_H
#define INSERTION_SORT_H

#include <stddef.h>

/* Add iterative insertion sort [l, r] */
void insertion_sort(void *vin, size_t l, size_t r);

/* Add iterative insertion sort with pivot [l, r] */
void insertion_sort_pivot(void *vin, size_t l, size_t r);

#endif

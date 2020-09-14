#ifndef MEMORY_MANAGER_H
#define MEMORY_MANAGER_H

#include <stddef.h>

/** Allocate a number of int arrays
 * Receives a pointer to pointer to pointer of int, equivalent to a pointer to
 * an array of arrays of int; the length of the array of arrays and the length
 * of each int array
 * The allocation uses the `calloc()` function.
 * Returns -1 on failure and 0 on success */
int allocate_int_arrays(int ***arr, size_t alen, size_t len);

/** Frees an array of int arrays
 * Each array, if not NULL, is freed and pointed to NULL */
void deallocate_int_arrays(int ***arr, size_t alen);

#endif

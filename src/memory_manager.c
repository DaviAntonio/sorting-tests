#include <stdlib.h>
#include "memory_manager.h"

int allocate_int_arrays(int ***arr, size_t alen, size_t len)
{
	for (size_t i = 0; i < alen; i++) {
		*arr[i] = calloc(sizeof(**arr), len);
		if (*arr[i] == NULL)
			return -1;
	}
	return 0;
}

void deallocate_int_arrays(int ***arr, size_t alen)
{
	for (size_t i = 0; i < alen; i++) {
		if (*arr[i] != NULL) {
			free(*arr[i]);
			*arr[i] = NULL;
		}
	}
}

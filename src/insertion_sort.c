#include "insertion_sort.h"
#include "int_arrays_sorting_macros.h"

void insertion_sort(void *vin, size_t l, size_t r)
{
	ITEM *v = vin;
	for (size_t i = l; i <= r; i++)
		for (size_t j = i; j > l; j--)
			SWAP_LESS(v[j], v[j-1]);
}

void insertion_sort_pivot(void *vin, size_t l, size_t r)
{
	ITEM *v = vin;
	for (size_t i = r; i > l; i--)
		SWAP_LESS(v[i], v[i - 1]);
	for (size_t i = l + 2; i <= r; i++) {
		size_t j = i;
		ITEM t = v[j];
		while (LESS(t, v[j - 1])) {
			v[j] = v[j - 1];
			j--;
		}
		v[j] = t;
	}
}

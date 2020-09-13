#include "selection_sort.h"
#include "int_arrays_sorting_macros.h"

void selection_sort(void *vin, size_t l, size_t r)
{
	ITEM *v = vin;
	for (size_t i = 0; i < r; i++) {
		size_t min = i;
		for (size_t j = i+1; j <= r; j++)
			if (LESS(v[j], v[min]))
				min = j;
		SWAP(v[min], v[i]);
	}
}

void selection_sort_rec(void *vin, size_t l, size_t r)
{
	if (l == r) return;
	ITEM *v = vin;
	size_t min = l;
	for (size_t j = l+1; j <= r; j++)
		if (LESS(v[j], v[min]))
			min = j;
	SWAP(v[min], v[l]);
	selection_sort_rec(v, l+1, r);
}

#include "selection_sort.h"

void selection_sort(ITEM *v, size_t l, size_t r)
{
	for (size_t i = 0; i < r; i++) {
		size_t min = i;
		for (size_t j = i+1; j <= r; j++)
			if (LESS(v[j], v[min]))
				min = j;
		EXCH(v[min], v[i]);
	}
}

void selection_sort_rec(ITEM *v, size_t l, size_t r)
{
	if (l == r) return;
	size_t min = l;
	for (size_t j = l+1; j <= r; j++)
		if (LESS(v[j], v[min]))
			min = j;
	EXCH(v[min], v[l]);
	selection_sort_rec(v, l+1, r);
}

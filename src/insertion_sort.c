#include "insertion_sort.h"

void insertion_sort(ITEM *v, size_t l, size_t r)
{
	for (size_t i = l; i <= r; i++)
		for (size_t j = i; j > l; j--)
			CMPEXCH(v[j], v[j-1]);
}

void insertion_sort_pivot(ITEM *v, size_t l, size_t r)
{
	for (size_t i = r; i > l; i--)
		CMPEXCH(v[i], v[i - 1]);
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

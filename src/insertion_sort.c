#include "insertion_sort.h"

void insertion_sort(ITEM *v, size_t l, size_t r)
{
	for (size_t i = l; i <= r; i++)
		for (size_t j = i; j > l; j--)
			CMPEXCH(v[j], v[j-1]);
}

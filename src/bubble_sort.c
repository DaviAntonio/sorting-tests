#include "bubble_sort.h"

void bubble_sort(ITEM *v, size_t l, size_t r)
{
	for (size_t i = l; i < r; i++)
		for (size_t j = l; j < r; j++)
			CMPEXCH(v[j+1], v[j]);
}

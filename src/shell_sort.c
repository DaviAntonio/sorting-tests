#include "shell_sort.h"
#include "int_arrays_sorting_macros.h"

/* Insertion sort with configurable hop on array [l, r] */
static void insertion_sort_h(void *vin, size_t l, size_t r, size_t h)
{
	ITEM *v = vin;
	for (size_t i = l + h; i <= r; i++) {
		size_t j = i;
		ITEM t = v[j];
		while (j >= l + h && LESS(t, v[j - h])) {
			v[j] = v[j - h];
			j -= h;
		}
		v[j] = t;
	}
}

void shell_sort(void *vin, size_t l, size_t r)
{
	ITEM *v = vin;
	size_t h;
	for (h = 1; h <= (r - l)/9; h = 3*h + 1);
	for (; h > 0; h = h/3)
		insertion_sort_h(v, l, r, h);
}

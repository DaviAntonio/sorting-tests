#include <string.h>
#include "insertion_sort.h"
#include "int_arrays_sorting_macros.h"

static struct counters insertion;
static struct counters insertion_pivot;

struct counters insertion_get_counters(void (*fp)(void *, size_t, size_t))
{
	if (fp == insertion_sort)
		return insertion;
	else if (fp == insertion_sort_pivot)
		return insertion_pivot;
	else
		return insertion;
}

void insertion_clear_counters(void (*fp)(void *, size_t, size_t))
{
	if (fp == insertion_sort)
		memset(&insertion, 0, sizeof(insertion));
	else if (fp == insertion_sort_pivot)
		memset(&insertion_pivot, 0, sizeof(insertion_pivot));
}

void insertion_sort(void *vin, size_t l, size_t r)
{
	INIT_COUNTERS(insertion);
	COUNT_CALLS;

	ITEM *v = vin;
	for (size_t i = l; i <= r; i++)
		for (size_t j = i; j > l; j--)
			SWAP_LESS(v[j], v[j-1]);
}

void insertion_sort_pivot(void *vin, size_t l, size_t r)
{
	INIT_COUNTERS(insertion_pivot);
	COUNT_CALLS;

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

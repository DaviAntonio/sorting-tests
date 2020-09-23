#include <string.h>
#include "selection_sort.h"
#include "int_arrays_sorting_macros.h"

static struct counters selection;
static struct counters selection_rec;

struct counters selection_get_counters(void (*fp)(void *, size_t, size_t))
{
	if (fp == selection_sort)
		return selection;
	else if (fp == selection_sort_rec)
		return selection_rec;
	else
		return selection;
}

void selection_clear_counters(void (*fp)(void *, size_t, size_t))
{
	if (fp == selection_sort)
		memset(&selection, 0, sizeof(selection));
	else if (fp == selection_sort_rec)
		memset(&selection_rec, 0, sizeof(selection_rec));

}

void selection_sort(void *vin, size_t l, size_t r)
{
	INIT_COUNTERS(selection);
	COUNT_CALLS;
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
	INIT_COUNTERS(selection_rec);
	COUNT_CALLS;
	if (l == r) return;
	ITEM *v = vin;
	size_t min = l;
	for (size_t j = l+1; j <= r; j++)
		if (LESS(v[j], v[min]))
			min = j;
	SWAP(v[min], v[l]);
	selection_sort_rec(v, l+1, r);
}

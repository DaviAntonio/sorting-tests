#include <string.h>
#include "quicksort.h"
#include "int_arrays_sorting_macros.h"

static struct counters partition_counter;
static struct counters quick;
static struct counters quick_median_3;
static struct counters quick_median_3_short;

struct counters quick_get_counters(void (*fp)(void *, size_t, size_t))
{
	if (fp == quicksort)
		return add_counters(quick, partition_counter);
	else if (fp == quicksort_median_3)
		return add_counters(quick_median_3, partition_counter);
	else if (fp == quicksort_median_3_short)
		return add_counters(quick_median_3_short, partition_counter);
	else
		return partition_counter;
}

void quick_clear_counters(void (*fp)(void *, size_t, size_t))
{
	memset(&partition_counter, 0, sizeof(partition_counter));
	if (fp == quicksort)
		memset(&quick, 0, sizeof(quick));
	else if (fp == quicksort_median_3)
		memset(&quick_median_3, 0, sizeof(quick_median_3));
	else if (fp ==quicksort_median_3_short)
		memset(&quick_median_3_short, 0, sizeof(quick_median_3_short));
}

/* Partition function according to Cormen */
static size_t partition(void *vin, size_t l, size_t r)
{
	INIT_COUNTERS(partition_counter);
	ITEM *v = vin;
	/** Pivot element */
	ITEM c = v[r];

	/** Pivot's final position */
	size_t j = l;

	for (size_t k = l; k < r; k++) {
		if (LESSEQ(v[k], c)) {
			SWAP(v[k], v[j]);
			j++;
		}
	}

	SWAP(v[j], v[r]);

	return j;
}

void quicksort(void *vin, size_t l, size_t r)
{
	INIT_COUNTERS(quick);
	COUNT_CALLS;
	if (r <= l) return;
	ITEM *v = vin;
	size_t j = partition(v, l, r);
	if (j > 0) quicksort(v, l, j - 1);
	quicksort(v, j + 1, r);
}

void quicksort_median_3(void *vin, size_t l, size_t r)
{
	INIT_COUNTERS(quick_median_3);
	COUNT_CALLS;
	if (r <= l) return;
	ITEM *v = vin;
	// Send the median of 3 to the end of the array
	size_t m = l + ((r - l) >> 1);
	SWAP_LESS(v[r], v[m]);
	SWAP_LESS(v[m], v[l]);
	SWAP_LESS(v[m], v[r]);
	size_t j = partition(v, l, r);
	if (j > 0) quicksort_median_3(v, l, j - 1);
	quicksort_median_3(v, j + 1, r);
}

void quicksort_median_3_short(void *vin, size_t l, size_t r)
{
	INIT_COUNTERS(quick_median_3_short);
	COUNT_CALLS;
	ITEM *v = vin;
	while (l < r) {
		// Send the median of 3 to the end of the array
		size_t m = l + ((r - l) >> 1);
		SWAP_LESS(v[r], v[m]);
		SWAP_LESS(v[m], v[l]);
		SWAP_LESS(v[m], v[r]);

		size_t j = partition(v, l, r);

		// Follow the shortest tail
		if (j - l < r - j) {
			if (j > 0) quicksort_median_3_short(v, l, j - 1);
			l = j + 1;
		} else {
			quicksort_median_3_short(v, j + 1, r);
			if (j > 0) r = j - 1;
		}
	}
}

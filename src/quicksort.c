#include "quicksort.h"
#include "int_arrays_sorting_macros.h"

/* Partition function according to Cormen */
static size_t partition(void *vin, size_t l, size_t r)
{
	ITEM *v = vin;
	/** Pivot element */
	ITEM c = v[r];

	/** Pivot's final position */
	size_t j = l;

	for (size_t k = l; k < r; k++) {
		if LESSEQ(v[k], c) {
			SWAP(v[k], v[j]);
			j++;
		}
	}

	SWAP(v[j], v[r]);

	return j;
}

void quicksort(void *vin, size_t l, size_t r)
{
	if (r <= l) return;
	ITEM *v = vin;
	size_t j = partition(v, l, r);
	if (j > 0) quicksort(v, l, j - 1);
	quicksort(v, j + 1, r);
}

void quicksort_median_3(void *vin, size_t l, size_t r)
{
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

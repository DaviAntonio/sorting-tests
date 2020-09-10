#include "quicksort.h"

/* Partition function according to Cormen */
static size_t partition(ITEM *v, size_t l, size_t r)
{
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

void quicksort(ITEM *v, size_t l, size_t r)
{
	if (r <= l) return;
	size_t j = partition(v, l, r);
	if (j > 0) quicksort(v, l, j - 1);
	quicksort(v, j + 1, r);
}

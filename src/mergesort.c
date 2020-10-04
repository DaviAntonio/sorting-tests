#include <stdlib.h>
#include <string.h>
#include "mergesort.h"
#include "int_arrays_sorting_macros.h"

static struct counters merge2_counter;
static struct counters merge;
static struct counters merge_i;

struct counters merge_get_counters(void (*fp)(void *, size_t, size_t))
{
	if (fp == mergesort)
		return add_counters(merge, merge2_counter);
	else if (fp == mergesort_i)
		return add_counters(merge_i, merge2_counter);
	else
		return merge2_counter;
}

void merge_clear_counters(void (*fp)(void *, size_t, size_t))
{
	memset(&merge2_counter, 0, sizeof(merge2_counter));
	if (fp == mergesort)
		memset(&merge, 0, sizeof(merge));
	else
		memset(&merge_i, 0, sizeof(merge_i));
}

static void merge2(void *vin, size_t l, size_t r1, size_t r2)
{
	INIT_COUNTERS(merge2_counter);

	ITEM *v = vin;

	size_t k = 0, i = l, j = r1 + 1;
	ITEM *v2 = malloc(sizeof(*v2) * (r2 - l + 1));
	if (v2 == NULL) return;

	while (i <= r1 && j <= r2) {
		if (LESSEQ(v[i], v[j]))
			v2[k++] = v[i++];
		else
			v2[k++] = v[j++];
	}

	while (i <= r1) v2[k++] = v[i++];
	while (j <= r2) v2[k++] = v[j++];

	for (i = l, k = 0; i <= r2; i++, k++)
		v[i] = v2[k];

	free(v2);
}

void mergesort(void *v, size_t l, size_t r)
{
	INIT_COUNTERS(merge);
	COUNT_CALLS;

	if (l >= r) return;
	size_t m = l + ((r - l) >> 1);
	mergesort(v, l, m);
	mergesort(v, m + 1, r);
	merge2(v, l, m, r);
}

void mergesort_i(void *v, size_t l, size_t r)
{
	INIT_COUNTERS(merge_i);
	COUNT_CALLS;

	// size of blocks to merge. Emulates the recursion, b = 1, 2, 4, ..., n
	size_t b = 1;

	while (b < r - l + 1) {
		size_t tl = l;
		// merge both sub-arrays until the end of the main array
		while (tl + b - 1 < r) {
			// Define the end of the sub-array that contains two sub-arrays
			size_t tr = tl + (b << 1) - 1;
			if (tr > r) tr = r;

			// Merge both halves of the sub-array
			merge2(v, tl, tl + b - 1, tr);

			// Walk to the next sub-array
			tl += (b << 1);
		}
		// Next sub-array size, emulates the recursion
		b <<= 1;
	}
}

#include <string.h>
#include "merge2.h"
#include "mergesort_iter.h"
#include "int_arrays_sorting_macros.h"

static struct counters cntrs;

struct timed_test_defs mergesort_iter_get_test_defs()
{
	return (struct timed_test_defs) {
		.test_name.name = "Merge sort",
		.test_name.type = "Iterative",
		.test_name.details = "",
		.fp = mergesort_iter,
		.clear_counters = mergesort_iter_clear_counters,
		.get_counters = mergesort_iter_get_counters
	};
}

void mergesort_iter_clear_counters()
{
	memset(&cntrs, 0, sizeof(cntrs));
	memset(&merge2_cntrs, 0, sizeof(merge2_cntrs));
}

struct counters mergesort_iter_get_counters()
{
	return add_counters(cntrs, merge2_cntrs);
}

void mergesort_iter(void *vin, size_t l, size_t r)
{
	INIT_COUNTERS(cntrs);
	COUNT_CALLS;

	ITEM *v = vin;

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

#include <string.h>
#include "cormen_partition.h"
#include "quicksort_rec_m3_short.h"
#include "int_arrays_sorting_macros.h"

static struct counters cntrs;

struct timed_test_defs quicksort_rec_m3_short_get_test_defs()
{
	return (struct timed_test_defs) {
		.test_name.name = "Quick sort",
		.test_name.type = "Recursive",
		.test_name.details = "Cormen partition; Median of 3; Shortest tail",
		.fp = quicksort_rec_m3_short,
		.clear_counters = quicksort_rec_m3_short_clear_counters,
		.get_counters = quicksort_rec_m3_short_get_counters
	};
}

void quicksort_rec_m3_short_clear_counters()
{
	memset(&cntrs, 0, sizeof(cntrs));
	memset(&partition_cntrs, 0, sizeof(partition_cntrs));
}

struct counters quicksort_rec_m3_short_get_counters()
{
	return add_counters(cntrs, partition_cntrs);
}

void quicksort_rec_m3_short(void *vin, size_t l, size_t r)
{
	INIT_COUNTERS(cntrs);
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
			if (j > 0) quicksort_rec_m3_short(v, l, j - 1);
			l = j + 1;
		} else {
			quicksort_rec_m3_short(v, j + 1, r);
			if (j > 0) r = j - 1;
		}
	}
}

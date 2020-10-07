#include <string.h>
#include "cormen_partition.h"
#include "quicksort_rec_m3.h"
#include "int_arrays_sorting_macros.h"

static struct counters cntrs;

/** Clears the counters */
static void quicksort_rec_m3_clear_counters();

/** Gets the counters */
static struct counters quicksort_rec_m3_get_counters();

struct timed_test_defs quicksort_rec_m3_get_test_defs()
{
	return (struct timed_test_defs) {
		.test_name.name = "Quick sort",
		.test_name.type = "Recursive",
		.test_name.details = "Cormen partition; Median of 3",
		.fp = quicksort_rec_m3,
		.clear_counters = quicksort_rec_m3_clear_counters,
		.get_counters = quicksort_rec_m3_get_counters
	};
}

static void quicksort_rec_m3_clear_counters()
{
	memset(&cntrs, 0, sizeof(cntrs));
	memset(&partition_cntrs, 0, sizeof(partition_cntrs));
}

static struct counters quicksort_rec_m3_get_counters()
{
	return add_counters(cntrs, partition_cntrs);
}

void quicksort_rec_m3(void *vin, size_t l, size_t r)
{
	INIT_COUNTERS(cntrs);
	COUNT_CALLS;
	if (r <= l) return;
	ITEM *v = vin;
	// Send the median of 3 to the end of the array
	size_t m = l + ((r - l) >> 1);
	SWAP_LESS(v[r], v[m]);
	SWAP_LESS(v[m], v[l]);
	SWAP_LESS(v[m], v[r]);
	size_t j = partition(v, l, r);
	if (j > 0) quicksort_rec_m3(v, l, j - 1);
	quicksort_rec_m3(v, j + 1, r);
}

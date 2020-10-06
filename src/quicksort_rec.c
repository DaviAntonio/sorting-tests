#include <string.h>
#include "cormen_partition.h"
#include "quicksort_rec.h"
#include "int_arrays_sorting_macros.h"

static struct counters cntrs;

struct timed_test_defs quicksort_rec_get_test_defs()
{
	return (struct timed_test_defs) {
		.test_name.name = "Quick sort",
		.test_name.type = "Recursive",
		.test_name.details = "Cormen partition",
		.fp = quicksort_rec,
		.clear_counters = quicksort_rec_clear_counters,
		.get_counters = quicksort_rec_get_counters
	};
}

void quicksort_rec_clear_counters()
{
	memset(&cntrs, 0, sizeof(cntrs));
	memset(&partition_cntrs, 0, sizeof(partition_cntrs));
}

struct counters quicksort_rec_get_counters()
{
	return add_counters(cntrs, partition_cntrs);
}

void quicksort_rec(void *vin, size_t l, size_t r)
{
	INIT_COUNTERS(cntrs);
	COUNT_CALLS;
	if (r <= l) return;
	ITEM *v = vin;
	size_t j = partition(v, l, r);
	if (j > 0) quicksort_rec(v, l, j - 1);
	quicksort_rec(v, j + 1, r);
}


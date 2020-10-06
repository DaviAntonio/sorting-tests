#include <string.h>
#include "merge2.h"
#include "mergesort_rec.h"
#include "int_arrays_sorting_macros.h"

static struct counters cntrs;

struct timed_test_defs mergesort_rec_get_test_defs()
{
	return (struct timed_test_defs) {
		.test_name.name = "Merge sort",
		.test_name.type = "Recursive",
		.test_name.details = "",
		.fp = mergesort_rec,
		.clear_counters = mergesort_rec_clear_counters,
		.get_counters = mergesort_rec_get_counters
	};
}

void mergesort_rec_clear_counters()
{
	memset(&cntrs, 0, sizeof(cntrs));
	memset(&merge2_cntrs, 0, sizeof(merge2_cntrs));
}

struct counters mergesort_rec_get_counters()
{
	return add_counters(cntrs, merge2_cntrs);
}

void mergesort_rec(void *vin, size_t l, size_t r)
{
	INIT_COUNTERS(cntrs);
	COUNT_CALLS;

	ITEM *v = vin;

	if (l >= r) return;
	size_t m = l + ((r - l) >> 1);
	mergesort_rec(v, l, m);
	mergesort_rec(v, m + 1, r);
	merge2(v, l, m, r);
}

#include <string.h>
#include "selectionsort_rec.h"
#include "int_arrays_sorting_macros.h"

static struct counters cntrs;

/** Clears the counters */
static void selectionsort_rec_clear_counters();

/** Gets the counters */
static struct counters selectionsort_rec_get_counters();

struct timed_test_defs selectionsort_rec_get_test_defs()
{
	return (struct timed_test_defs) {
		.test_name.name = "Selection sort",
		.test_name.type = "Recursive",
		.test_name.details = "",
		.fp = selectionsort_rec,
		.clear_counters = selectionsort_rec_clear_counters,
		.get_counters = selectionsort_rec_get_counters
	};
}

static void selectionsort_rec_clear_counters()
{
	memset(&cntrs, 0, sizeof(cntrs));
}

static struct counters selectionsort_rec_get_counters()
{
	return cntrs;
}

void selectionsort_rec(void *vin, size_t l, size_t r)
{
	INIT_COUNTERS(cntrs);
	COUNT_CALLS;
	if (l == r) return;
	ITEM *v = vin;
	size_t min = l;
	for (size_t j = l+1; j <= r; j++)
		if (LESS(v[j], v[min]))
			min = j;
	SWAP(v[min], v[l]);
	selectionsort_rec(v, l+1, r);
}

#include <string.h>
#include "selectionsort_iter.h"
#include "int_arrays_sorting_macros.h"

static struct counters cntrs;

/** Clears the counters */
static void selectionsort_iter_clear_counters();

/** Gets the counters */
static struct counters selectionsort_iter_get_counters();

struct timed_test_defs selectionsort_iter_get_test_defs()
{
	return (struct timed_test_defs) {
		.test_name.name = "Selection sort",
		.test_name.type = "Iterative",
		.test_name.details = "",
		.fp = selectionsort_iter,
		.clear_counters = selectionsort_iter_clear_counters,
		.get_counters = selectionsort_iter_get_counters
	};
}

static void selectionsort_iter_clear_counters()
{
	memset(&cntrs, 0, sizeof(cntrs));
}

static struct counters selectionsort_iter_get_counters()
{
	return cntrs;
}

void selectionsort_iter(void *vin, size_t l, size_t r)
{
	INIT_COUNTERS(cntrs);
	COUNT_CALLS;
	ITEM *v = vin;
	for (size_t i = 0; i < r; i++) {
		size_t min = i;
		for (size_t j = i+1; j <= r; j++)
			if (LESS(v[j], v[min]))
				min = j;
		SWAP(v[min], v[i]);
	}
}


#include <string.h>
#include "shellsort_iter.h"
#include "insertionsort_h.h"
#include "int_arrays_sorting_macros.h"

static struct counters cntrs;

/** Clears the counters */
static void shellsort_iter_clear_counters();

/** Gets the counters */
static struct counters shellsort_iter_get_counters();

struct timed_test_defs shellsort_iter_get_test_defs()
{
	return (struct timed_test_defs) {
		.test_name.name = "Shell sort",
		.test_name.type = "Iterative",
		.test_name.details = "Knuth 1969 OESIS A003462",
		.fp = shellsort_iter,
		.clear_counters = shellsort_iter_clear_counters,
		.get_counters = shellsort_iter_get_counters
	};
}

static void shellsort_iter_clear_counters()
{
	memset(&insertionsort_h_cntrs, 0, sizeof(insertionsort_h_cntrs));
	memset(&cntrs, 0, sizeof(cntrs));
}

static struct counters shellsort_iter_get_counters()
{
	return add_counters(cntrs, insertionsort_h_cntrs);
}

void shellsort_iter(void *vin, size_t l, size_t r){
	INIT_COUNTERS(cntrs);
	COUNT_CALLS;
	ITEM *v = vin;
	size_t h;
	for (h = 1; h <= (r - l) / 9; h = 3 * h + 1);
	for (; h > 0; h = h / 3)
		insertionsort_h(v, l, r, h);
}

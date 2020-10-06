#include <string.h>
#include "bubblesort_iter.h"
#include "int_arrays_sorting_macros.h"

static struct counters cntrs;

struct timed_test_defs bubblesort_iter_get_test_defs()
{
	return (struct timed_test_defs) {
		.test_name.name = "Bubble sort",
		.test_name.type = "Iterative",
		.test_name.details = "",
		.fp = bubblesort_iter,
		.clear_counters = bubblesort_iter_clear_counters,
		.get_counters = bubblesort_iter_get_counters
	};
}

void bubblesort_iter_clear_counters()
{
	memset(&cntrs, 0, sizeof(cntrs));
}

struct counters bubblesort_iter_get_counters()
{
	return cntrs;
}

void bubblesort_iter(void *vin, size_t l, size_t r)
{
	INIT_COUNTERS(cntrs);
	COUNT_CALLS;

	ITEM *v = vin;
	for (size_t i = l; i < r; i++)
		for (size_t j = l; j < r; j++)
			SWAP_LESS(v[j+1], v[j]);
}

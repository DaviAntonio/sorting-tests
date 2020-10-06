#include <string.h>
#include "bubblesort_rec.h"
#include "int_arrays_sorting_macros.h"

static struct counters cntrs;

struct timed_test_defs bubblesort_rec_get_test_defs()
{
	return (struct timed_test_defs) {
		.test_name.name = "Bubble sort",
		.test_name.type = "Recursive",
		.test_name.details = "",
		.fp = bubblesort_rec,
		.clear_counters = bubblesort_rec_clear_counters,
		.get_counters = bubblesort_rec_get_counters
	};
}

void bubblesort_rec_clear_counters()
{
	memset(&cntrs, 0, sizeof(cntrs));
}

struct counters bubblesort_rec_get_counters()
{
	return cntrs;
}

void bubblesort_rec(void *vin, size_t l, size_t r)
{
	INIT_COUNTERS(cntrs);
	COUNT_CALLS;

	ITEM *v = vin;
	if (r == l) return;

	for (size_t i = l; i < r; i++)
		SWAP_LESS(v[i+1], v[i]);

	bubblesort_rec(v, l, r-1);
}


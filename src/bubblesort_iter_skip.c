#include <string.h>
#include "bubblesort_iter_skip.h"
#include "int_arrays_sorting_macros.h"

static struct counters cntrs;

struct timed_test_defs bubblesort_iter_skip_get_test_defs()
{
	return (struct timed_test_defs) {
		.test_name.name = "Bubble sort",
		.test_name.type = "Iterative",
		.test_name.details = "Skips already ordered",
		.fp = bubblesort_iter_skip,
		.clear_counters = bubblesort_iter_skip_clear_counters,
		.get_counters = bubblesort_iter_skip_get_counters
	};
}

void bubblesort_iter_skip_clear_counters()
{
	memset(&cntrs, 0, sizeof(cntrs));
}

struct counters bubblesort_iter_skip_get_counters()
{
	return cntrs;
}

void bubblesort_iter_skip(void *vin, size_t l, size_t r)
{
	INIT_COUNTERS(cntrs);
	COUNT_CALLS;

	ITEM *v = vin;
	size_t nr = r;

	while (r > l) {
		nr = l;
		for (size_t i = l+1; i <= r; i++) {
			if (LESS(v[i], v[i-1])) {
				SWAP(v[i], v[i-1]);
				nr = i;
			}
		}
		r = nr;
	}
}

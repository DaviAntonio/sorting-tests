#include <string.h>
#include "insertionsort_iter.h"
#include "int_arrays_sorting_macros.h"

static struct counters cntrs;

struct timed_test_defs insertionsort_iter_get_test_defs()
{
	return (struct timed_test_defs) {
		.test_name.name = "Insertion sort",
		.test_name.type = "Iterative",
		.test_name.details = "",
		.fp = insertionsort_iter,
		.clear_counters = insertionsort_iter_clear_counters,
		.get_counters = insertionsort_iter_get_counters
	};
}

void insertionsort_iter_clear_counters()
{
	memset(&cntrs, 0, sizeof(cntrs));
}

struct counters insertionsort_iter_get_counters()
{
	return cntrs;
}

void insertionsort_iter(void *vin, size_t l, size_t r)
{
	INIT_COUNTERS(cntrs);
	COUNT_CALLS;

	ITEM *v = vin;
	for (size_t i = l; i <= r; i++)
		for (size_t j = i; j > l; j--)
			SWAP_LESS(v[j], v[j-1]);
}

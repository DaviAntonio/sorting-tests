#include <string.h>
#include "insertionsort_iter_pivot.h"
#include "int_arrays_sorting_macros.h"

static struct counters cntrs;

/** Clears the counters */
static void insertionsort_iter_pivot_clear_counters();

/** Gets the counters */
static struct counters insertionsort_iter_pivot_get_counters();

struct timed_test_defs insertionsort_iter_pivot_get_test_defs()
{
	return (struct timed_test_defs) {
		.test_name.name = "Insertion sort",
		.test_name.type = "Iterative",
		.test_name.details = "Pivot",
		.fp = insertionsort_iter_pivot,
		.clear_counters = insertionsort_iter_pivot_clear_counters,
		.get_counters = insertionsort_iter_pivot_get_counters
	};
}

static void insertionsort_iter_pivot_clear_counters()
{
	memset(&cntrs, 0, sizeof(cntrs));
}

static struct counters insertionsort_iter_pivot_get_counters()
{
	return cntrs;
}

void insertionsort_iter_pivot(void *vin, size_t l, size_t r)
{
	INIT_COUNTERS(cntrs);
	COUNT_CALLS;

	ITEM *v = vin;
	for (size_t i = r; i > l; i--)
		SWAP_LESS(v[i], v[i - 1]);
	for (size_t i = l + 2; i <= r; i++) {
		size_t j = i;
		ITEM t = v[j];
		while (LESS(t, v[j - 1])) {
			v[j] = v[j - 1];
			j--;
		}
		v[j] = t;
	}
}

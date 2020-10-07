#include <stdbool.h>
#include <string.h>
#include "bubblesort_iter_while.h"
#include "int_arrays_sorting_macros.h"

static struct counters cntrs;

/** Clears the counters */
static void bubblesort_iter_while_clear_counters();

/** Gets the counters */
static struct counters bubblesort_iter_while_get_counters();

struct timed_test_defs bubblesort_iter_while_get_test_defs()
{
	return (struct timed_test_defs) {
		.test_name.name = "Bubble sort",
		.test_name.type = "Iterative",
		.test_name.details = "No nested for loops",
		.fp = bubblesort_iter_while,
		.clear_counters = bubblesort_iter_while_clear_counters,
		.get_counters = bubblesort_iter_while_get_counters
	};
}

static void bubblesort_iter_while_clear_counters()
{
	memset(&cntrs, 0, sizeof(cntrs));
}

static struct counters bubblesort_iter_while_get_counters()
{
	return cntrs;
}

void bubblesort_iter_while(void *vin, size_t l, size_t r)
{
	INIT_COUNTERS(cntrs);
	COUNT_CALLS;

	ITEM *v = vin;
	bool inversion = true;

	while (inversion) {
		inversion = false;
		/* Must include the last position as it compares the current
		 * element with the previous one */
		for (size_t i = l+1; i <= r; i++) {
			if (LESS(v[i], v[i-1])) {
				SWAP(v[i], v[i-1]);
				inversion = true;
			}
		}
	}
}

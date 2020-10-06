#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tester.h"
#include "memory_manager.h"
#include "selectionsort.h"
#include "bubblesort.h"
#include "shellsort.h"
#include "insertionsort.h"
#include "quicksort.h"
#include "mergesort.h"

#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

#define ITEMS_NUM (200000)

int cmp_ints(const void *i1, const void *i2)
{
	return (*(int *)i1)-(*(int *)i2);
}

int main()
{
	int *random_data = NULL;
	int *expected = NULL;
	int *ordered = NULL;
	int *reverse = NULL;

	int **arrays[] = {&random_data, &expected, &ordered, &reverse};

	// Allocate all
	if (allocate_int_arrays(arrays, ARRAY_SIZE(arrays), ITEMS_NUM)) {
		printf("Allocation failure\n");
		deallocate_int_arrays(arrays, ARRAY_SIZE(arrays));
		return -1;
	}

	// Initialise random numbers
	printf("generating %d numbers\n", ITEMS_NUM);
	srand(0);
	for (size_t i = 0; i < ITEMS_NUM; i++) {
		random_data[i] = rand();
#ifdef DBGPRINT
		fprintf(stderr, "random_data[%zu]=%d\n", i, random_data[i]);
#endif
	}

	printf("initialising\n");
	memcpy(expected, random_data, sizeof(*expected) * ITEMS_NUM);

	printf("sorting\n");
	// sort the array using standard functions
	qsort(expected, ITEMS_NUM, sizeof(*expected), cmp_ints);

	// Copy to ordered array
	memcpy(ordered, expected, sizeof(*ordered) * ITEMS_NUM);

	printf("reversing\n");
	// reverse the sorted array
	for (size_t i = 0, j = ITEMS_NUM-1; i < ITEMS_NUM; i++, j--) {
		reverse[i] = expected[j];
#ifdef DBGPRINT
		fprintf(stderr, "reverse[%zu]=%d\n", i, reverse[i]);
#endif
	}

	struct timed_test tests[] = {
		// Selection sort iterative
		{
			.defs = selectionsort_iter_get_test_defs(),
			.input_descr = "Random",
			.input = random_data,
			.input_l = 0,
			.input_r = ITEMS_NUM - 1,
			.expected = expected,
			.data_size = sizeof(*random_data) * ITEMS_NUM,
			.elem_size = sizeof(*random_data)
		},
		{
			.defs = selectionsort_iter_get_test_defs(),
			.input_descr = "Reverse",
			.input = reverse,
			.input_l = 0,
			.input_r = ITEMS_NUM - 1,
			.expected = expected,
			.data_size = sizeof(*reverse) * ITEMS_NUM,
			.elem_size = sizeof(*reverse)
		},
		{
			.defs = selectionsort_iter_get_test_defs(),
			.input_descr = "Ordered",
			.input = ordered,
			.input_l = 0,
			.input_r = ITEMS_NUM - 1,
			.expected = expected,
			.data_size = sizeof(*ordered) * ITEMS_NUM,
			.elem_size = sizeof(*ordered)
		},
		// Selection sort recursive
		{
			.defs = selectionsort_rec_get_test_defs(),
			.input_descr = "Random",
			.input = random_data,
			.input_l = 0,
			.input_r = ITEMS_NUM - 1,
			.expected = expected,
			.data_size = sizeof(*random_data) * ITEMS_NUM,
			.elem_size = sizeof(*random_data)
		},
		{
			.defs = selectionsort_rec_get_test_defs(),
			.input_descr = "Reverse",
			.input = reverse,
			.input_l = 0,
			.input_r = ITEMS_NUM - 1,
			.expected = expected,
			.data_size = sizeof(*reverse) * ITEMS_NUM,
			.elem_size = sizeof(*reverse)
		},
		{
			.defs = selectionsort_rec_get_test_defs(),
			.input_descr = "Ordered",
			.input = ordered,
			.input_l = 0,
			.input_r = ITEMS_NUM - 1,
			.expected = expected,
			.data_size = sizeof(*ordered) * ITEMS_NUM,
			.elem_size = sizeof(*ordered)
		},
		// Bubble sort iterative
		{
			.defs = bubblesort_iter_get_test_defs(),
			.input_descr = "Random",
			.input = random_data,
			.input_l = 0,
			.input_r = ITEMS_NUM - 1,
			.expected = expected,
			.data_size = sizeof(*random_data) * ITEMS_NUM,
			.elem_size = sizeof(*random_data)
		},
		{
			.defs = bubblesort_iter_get_test_defs(),
			.input_descr = "Reverse",
			.input = reverse,
			.input_l = 0,
			.input_r = ITEMS_NUM - 1,
			.expected = expected,
			.data_size = sizeof(*reverse) * ITEMS_NUM,
			.elem_size = sizeof(*reverse)
		},
		{
			.defs = bubblesort_iter_get_test_defs(),
			.input_descr = "Ordered",
			.input = ordered,
			.input_l = 0,
			.input_r = ITEMS_NUM - 1,
			.expected = expected,
			.data_size = sizeof(*ordered) * ITEMS_NUM,
			.elem_size = sizeof(*ordered)
		},
		// Bubble sort recursive
		{
			.defs = bubblesort_rec_get_test_defs(),
			.input_descr = "Random",
			.input = random_data,
			.input_l = 0,
			.input_r = ITEMS_NUM - 1,
			.expected = expected,
			.data_size = sizeof(*random_data) * ITEMS_NUM,
			.elem_size = sizeof(*random_data)
		},
		{
			.defs = bubblesort_rec_get_test_defs(),
			.input_descr = "Reverse",
			.input = reverse,
			.input_l = 0,
			.input_r = ITEMS_NUM - 1,
			.expected = expected,
			.data_size = sizeof(*reverse) * ITEMS_NUM,
			.elem_size = sizeof(*reverse)
		},
		{
			.defs = bubblesort_rec_get_test_defs(),
			.input_descr = "Ordered",
			.input = ordered,
			.input_l = 0,
			.input_r = ITEMS_NUM - 1,
			.expected = expected,
			.data_size = sizeof(*ordered) * ITEMS_NUM,
			.elem_size = sizeof(*ordered)
		},
		// Bubble sort iterative (no nested for loops)
		{
			.defs = bubblesort_iter_while_get_test_defs(),
			.input_descr = "Random",
			.input = random_data,
			.input_l = 0,
			.input_r = ITEMS_NUM - 1,
			.expected = expected,
			.data_size = sizeof(*random_data) * ITEMS_NUM,
			.elem_size = sizeof(*random_data)
		},
		{
			.defs = bubblesort_iter_while_get_test_defs(),
			.input_descr = "Reverse",
			.input = reverse,
			.input_l = 0,
			.input_r = ITEMS_NUM - 1,
			.expected = expected,
			.data_size = sizeof(*reverse) * ITEMS_NUM,
			.elem_size = sizeof(*reverse)
		},
		{
			.defs = bubblesort_iter_while_get_test_defs(),
			.input_descr = "Ordered",
			.input = ordered,
			.input_l = 0,
			.input_r = ITEMS_NUM - 1,
			.expected = expected,
			.data_size = sizeof(*ordered) * ITEMS_NUM,
			.elem_size = sizeof(*ordered)
		},
		// Bubble sort optimised iterative
		{
			.defs = bubblesort_iter_skip_get_test_defs(),
			.input_descr = "Random",
			.input = random_data,
			.input_l = 0,
			.input_r = ITEMS_NUM - 1,
			.expected = expected,
			.data_size = sizeof(*random_data) * ITEMS_NUM,
			.elem_size = sizeof(*random_data)
		},
		{
			.defs = bubblesort_iter_skip_get_test_defs(),
			.input_descr = "Reverse",
			.input = reverse,
			.input_l = 0,
			.input_r = ITEMS_NUM - 1,
			.expected = expected,
			.data_size = sizeof(*reverse) * ITEMS_NUM,
			.elem_size = sizeof(*reverse)
		},
		{
			.defs = bubblesort_iter_skip_get_test_defs(),
			.input_descr = "Ordered",
			.input = ordered,
			.input_l = 0,
			.input_r = ITEMS_NUM - 1,
			.expected = expected,
			.data_size = sizeof(*ordered) * ITEMS_NUM,
			.elem_size = sizeof(*ordered)
		},
		// Shell sort
		{
			.defs = shellsort_iter_get_test_defs(),
			.input_descr = "Random",
			.input = random_data,
			.input_l = 0,
			.input_r = ITEMS_NUM - 1,
			.expected = expected,
			.data_size = sizeof(*random_data) * ITEMS_NUM,
			.elem_size = sizeof(*random_data)
		},
		{
			.defs = shellsort_iter_get_test_defs(),
			.input_descr = "Reverse",
			.input = reverse,
			.input_l = 0,
			.input_r = ITEMS_NUM - 1,
			.expected = expected,
			.data_size = sizeof(*reverse) * ITEMS_NUM,
			.elem_size = sizeof(*reverse)
		},
		{
			.defs = shellsort_iter_get_test_defs(),
			.input_descr = "Ordered",
			.input = ordered,
			.input_l = 0,
			.input_r = ITEMS_NUM - 1,
			.expected = expected,
			.data_size = sizeof(*ordered) * ITEMS_NUM,
			.elem_size = sizeof(*ordered)
		},
		// Insertion sort iterative
		{
			.defs = insertionsort_iter_get_test_defs(),
			.input_descr = "Random",
			.input = random_data,
			.input_l = 0,
			.input_r = ITEMS_NUM - 1,
			.expected = expected,
			.data_size = sizeof(*random_data) * ITEMS_NUM,
			.elem_size = sizeof(*random_data)
		},
		{
			.defs = insertionsort_iter_get_test_defs(),
			.input_descr = "Reverse",
			.input = reverse,
			.input_l = 0,
			.input_r = ITEMS_NUM - 1,
			.expected = expected,
			.data_size = sizeof(*reverse) * ITEMS_NUM,
			.elem_size = sizeof(*reverse)
		},
		{
			.defs = insertionsort_iter_get_test_defs(),
			.input_descr = "Ordered",
			.input = ordered,
			.input_l = 0,
			.input_r = ITEMS_NUM - 1,
			.expected = expected,
			.data_size = sizeof(*ordered) * ITEMS_NUM,
			.elem_size = sizeof(*ordered)
		},
		// Insertion sort iterative (pivot)
		{
			.defs = insertionsort_iter_pivot_get_test_defs(),
			.input_descr = "Random",
			.input = random_data,
			.input_l = 0,
			.input_r = ITEMS_NUM - 1,
			.expected = expected,
			.data_size = sizeof(*random_data) * ITEMS_NUM,
			.elem_size = sizeof(*random_data)
		},
		{
			.defs = insertionsort_iter_pivot_get_test_defs(),
			.input_descr = "Reverse",
			.input = reverse,
			.input_l = 0,
			.input_r = ITEMS_NUM - 1,
			.expected = expected,
			.data_size = sizeof(*reverse) * ITEMS_NUM,
			.elem_size = sizeof(*reverse)
		},
		{
			.defs = insertionsort_iter_pivot_get_test_defs(),
			.input_descr = "Ordered",
			.input = ordered,
			.input_l = 0,
			.input_r = ITEMS_NUM - 1,
			.expected = expected,
			.data_size = sizeof(*ordered) * ITEMS_NUM,
			.elem_size = sizeof(*ordered)
		},
		// Quicksort recursive
		{
			.defs = quicksort_rec_get_test_defs(),
			.input_descr = "Random",
			.input = random_data,
			.input_l = 0,
			.input_r = ITEMS_NUM - 1,
			.expected = expected,
			.data_size = sizeof(*random_data) * ITEMS_NUM,
			.elem_size = sizeof(*random_data)
		},
		{
			.defs = quicksort_rec_get_test_defs(),
			.input_descr = "Reverse",
			.input = reverse,
			.input_l = 0,
			.input_r = ITEMS_NUM - 1,
			.expected = expected,
			.data_size = sizeof(*reverse) * ITEMS_NUM,
			.elem_size = sizeof(*reverse)
		},
		{
			.defs = quicksort_rec_get_test_defs(),
			.input_descr = "Ordered",
			.input = ordered,
			.input_l = 0,
			.input_r = ITEMS_NUM - 1,
			.expected = expected,
			.data_size = sizeof(*ordered) * ITEMS_NUM,
			.elem_size = sizeof(*ordered)
		},
		// Quicksort recursive (median 3)
		{
			.defs = quicksort_rec_m3_get_test_defs(),
			.input_descr = "Random",
			.input = random_data,
			.input_l = 0,
			.input_r = ITEMS_NUM - 1,
			.expected = expected,
			.data_size = sizeof(*random_data) * ITEMS_NUM,
			.elem_size = sizeof(*random_data)
		},
		{
			.defs = quicksort_rec_m3_get_test_defs(),
			.input_descr = "Reverse",
			.input = reverse,
			.input_l = 0,
			.input_r = ITEMS_NUM - 1,
			.expected = expected,
			.data_size = sizeof(*reverse) * ITEMS_NUM,
			.elem_size = sizeof(*reverse)
		},
		{
			.defs = quicksort_rec_m3_get_test_defs(),
			.input_descr = "Ordered",
			.input = ordered,
			.input_l = 0,
			.input_r = ITEMS_NUM - 1,
			.expected = expected,
			.data_size = sizeof(*ordered) * ITEMS_NUM,
			.elem_size = sizeof(*ordered)
		},
		// quicksort recursive (median 3 shortest tail)
		{
			.defs = quicksort_rec_m3_short_get_test_defs(),
			.input_descr = "Random",
			.input = random_data,
			.input_l = 0,
			.input_r = ITEMS_NUM - 1,
			.expected = expected,
			.data_size = sizeof(*random_data) * ITEMS_NUM,
			.elem_size = sizeof(*random_data)
		},
		{
			.defs = quicksort_rec_m3_short_get_test_defs(),
			.input_descr = "Reverse",
			.input = reverse,
			.input_l = 0,
			.input_r = ITEMS_NUM - 1,
			.expected = expected,
			.data_size = sizeof(*reverse) * ITEMS_NUM,
			.elem_size = sizeof(*reverse)
		},
		{
			.defs = quicksort_rec_m3_short_get_test_defs(),
			.input_descr = "Ordered",
			.input = ordered,
			.input_l = 0,
			.input_r = ITEMS_NUM - 1,
			.expected = expected,
			.data_size = sizeof(*ordered) * ITEMS_NUM,
			.elem_size = sizeof(*ordered)
		},
		// mergesort recursive
		{
			.defs = mergesort_rec_get_test_defs(),
			.input_descr = "Random",
			.input = random_data,
			.input_l = 0,
			.input_r = ITEMS_NUM - 1,
			.expected = expected,
			.data_size = sizeof(*random_data) * ITEMS_NUM,
			.elem_size = sizeof(*random_data)
		},
		{
			.defs = mergesort_rec_get_test_defs(),
			.input_descr = "Reverse",
			.input = reverse,
			.input_l = 0,
			.input_r = ITEMS_NUM - 1,
			.expected = expected,
			.data_size = sizeof(*reverse) * ITEMS_NUM,
			.elem_size = sizeof(*reverse)
		},
		{
			.defs = mergesort_rec_get_test_defs(),
			.input_descr = "Ordered",
			.input = ordered,
			.input_l = 0,
			.input_r = ITEMS_NUM - 1,
			.expected = expected,
			.data_size = sizeof(*ordered) * ITEMS_NUM,
			.elem_size = sizeof(*ordered)
		},
		// mergesort iterative
		{
			.defs = mergesort_iter_get_test_defs(),
			.input_descr = "Random",
			.input = random_data,
			.input_l = 0,
			.input_r = ITEMS_NUM - 1,
			.expected = expected,
			.data_size = sizeof(*random_data) * ITEMS_NUM,
			.elem_size = sizeof(*random_data)
		},
		{
			.defs = mergesort_iter_get_test_defs(),
			.input_descr = "Reverse",
			.input = reverse,
			.input_l = 0,
			.input_r = ITEMS_NUM - 1,
			.expected = expected,
			.data_size = sizeof(*reverse) * ITEMS_NUM,
			.elem_size = sizeof(*reverse)
		},
		{
			.defs = mergesort_iter_get_test_defs(),
			.input_descr = "Ordered",
			.input = ordered,
			.input_l = 0,
			.input_r = ITEMS_NUM - 1,
			.expected = expected,
			.data_size = sizeof(*ordered) * ITEMS_NUM,
			.elem_size = sizeof(*ordered)
		}
	};

	for (size_t i = 0; i < ARRAY_SIZE(tests); i++) {
		int result = run_timed_test(&tests[i]);
		char test_success[] = "OK";
		char test_fail[] = "FAIL";
		char *test_result;
		if (result) {
			fprintf(stderr, "Test failed, returned: %d\n", result);
		} else {
			test_result = (tests[i].result) ? test_fail : test_success;
			printf("%s %s %s (status %d)"
				" (%f ms, %lu swaps, %lu comparisons, %lu calls) %s\n",
				tests[i].defs.test_name.name, tests[i].defs.test_name.type,
				tests[i].defs.test_name.details, tests[i].status,
				1e3f * (tests[i].time.tv_sec
					+ tests[i].time.tv_nsec / 1e9f),
				tests[i].cntrs.swps, tests[i].cntrs.cmps,
				tests[i].cntrs.calls, test_result);
		}
	}

	deallocate_int_arrays(arrays, ARRAY_SIZE(arrays));

	return 0;
}

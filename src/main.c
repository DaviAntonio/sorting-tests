#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tester.h"
#include "memory_manager.h"
#include "selection_sort.h"
#include "bubble_sort.h"
#include "shell_sort.h"
#include "insertion_sort.h"
#include "quicksort.h"

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
			.name = "Selection Sort Iterative Random",
			.fp = selection_sort,
			.clear_counters = selection_clear_counters,
			.get_counters = selection_get_counters,
			.input = random_data,
			.input_l = 0,
			.input_r = ITEMS_NUM - 1,
			.expected = expected,
			.data_size = sizeof(*random_data) * ITEMS_NUM,
			.elem_size = sizeof(*random_data)
		},
		{
			.name = "Selection Sort Iterative Reverse",
			.fp = selection_sort,
			.clear_counters = selection_clear_counters,
			.get_counters = selection_get_counters,
			.input = reverse,
			.input_l = 0,
			.input_r = ITEMS_NUM - 1,
			.expected = expected,
			.data_size = sizeof(*reverse) * ITEMS_NUM,
			.elem_size = sizeof(*reverse)
		},
		{
			.name = "Selection Sort Iterative Ordered",
			.fp = selection_sort,
			.clear_counters = selection_clear_counters,
			.get_counters = selection_get_counters,
			.input = ordered,
			.input_l = 0,
			.input_r = ITEMS_NUM - 1,
			.expected = expected,
			.data_size = sizeof(*ordered) * ITEMS_NUM,
			.elem_size = sizeof(*ordered)
		},
		// Selection sort recursive
		{
			.name = "Selection Sort Recursive Random",
			.fp = selection_sort_rec,
			.clear_counters = selection_clear_counters,
			.get_counters = selection_get_counters,
			.input = random_data,
			.input_l = 0,
			.input_r = ITEMS_NUM - 1,
			.expected = expected,
			.data_size = sizeof(*random_data) * ITEMS_NUM,
			.elem_size = sizeof(*random_data)
		},
				{
			.name = "Selection Sort Recursive Reverse",
			.fp = selection_sort_rec,
			.clear_counters = selection_clear_counters,
			.get_counters = selection_get_counters,
			.input = reverse,
			.input_l = 0,
			.input_r = ITEMS_NUM - 1,
			.expected = expected,
			.data_size = sizeof(*reverse) * ITEMS_NUM,
			.elem_size = sizeof(*reverse)
		},
		{
			.name = "Selection Sort Recursive Ordered",
			.fp = selection_sort_rec,
			.clear_counters = selection_clear_counters,
			.get_counters = selection_get_counters,
			.input = ordered,
			.input_l = 0,
			.input_r = ITEMS_NUM - 1,
			.expected = expected,
			.data_size = sizeof(*ordered) * ITEMS_NUM,
			.elem_size = sizeof(*ordered)
		},
		// Bubble sort iterative
		{
			.name = "Bubble Sort Iterative Random",
			.fp = bubble_sort,
			.clear_counters = bubble_clear_counters,
			.get_counters = bubble_get_counters,
			.input = random_data,
			.input_l = 0,
			.input_r = ITEMS_NUM - 1,
			.expected = expected,
			.data_size = sizeof(*random_data) * ITEMS_NUM,
			.elem_size = sizeof(*random_data)
		},
		{
			.name = "Bubble Sort Iterative Reverse",
			.fp = bubble_sort,
			.clear_counters = bubble_clear_counters,
			.get_counters = bubble_get_counters,
			.input = reverse,
			.input_l = 0,
			.input_r = ITEMS_NUM - 1,
			.expected = expected,
			.data_size = sizeof(*reverse) * ITEMS_NUM,
			.elem_size = sizeof(*reverse)
		},
		{
			.name = "Bubble Sort Iterative Ordered",
			.fp = bubble_sort,
			.clear_counters = bubble_clear_counters,
			.get_counters = bubble_get_counters,
			.input = ordered,
			.input_l = 0,
			.input_r = ITEMS_NUM - 1,
			.expected = expected,
			.data_size = sizeof(*ordered) * ITEMS_NUM,
			.elem_size = sizeof(*ordered)
		},
		// Bubble sort recursive
		{
			.name = "Bubble Sort Recursive Random",
			.fp = bubble_sort_rec,
			.clear_counters = bubble_clear_counters,
			.get_counters = bubble_get_counters,
			.input = random_data,
			.input_l = 0,
			.input_r = ITEMS_NUM - 1,
			.expected = expected,
			.data_size = sizeof(*random_data) * ITEMS_NUM,
			.elem_size = sizeof(*random_data)
		},
		{
			.name = "Bubble Sort Recursive Reverse",
			.fp = bubble_sort_rec,
			.clear_counters = bubble_clear_counters,
			.get_counters = bubble_get_counters,
			.input = reverse,
			.input_l = 0,
			.input_r = ITEMS_NUM - 1,
			.expected = expected,
			.data_size = sizeof(*reverse) * ITEMS_NUM,
			.elem_size = sizeof(*reverse)
		},
		{
			.name = "Bubble Sort Recursive Ordered",
			.fp = bubble_sort_rec,
			.clear_counters = bubble_clear_counters,
			.get_counters = bubble_get_counters,
			.input = ordered,
			.input_l = 0,
			.input_r = ITEMS_NUM - 1,
			.expected = expected,
			.data_size = sizeof(*ordered) * ITEMS_NUM,
			.elem_size = sizeof(*ordered)
		},
		// Bubble sort iterative (no nested for loops)
		{
			.name = "Bubble Sort Iterative (no nested for loops) Random",
			.fp = bubble_sort_optim,
			.clear_counters = bubble_clear_counters,
			.get_counters = bubble_get_counters,
			.input = random_data,
			.input_l = 0,
			.input_r = ITEMS_NUM - 1,
			.expected = expected,
			.data_size = sizeof(*random_data) * ITEMS_NUM,
			.elem_size = sizeof(*random_data)
		},
		{
			.name = "Bubble Sort Iterative (no nested for loops) Reverse",
			.fp = bubble_sort_optim,
			.clear_counters = bubble_clear_counters,
			.get_counters = bubble_get_counters,
			.input = reverse,
			.input_l = 0,
			.input_r = ITEMS_NUM - 1,
			.expected = expected,
			.data_size = sizeof(*reverse) * ITEMS_NUM,
			.elem_size = sizeof(*reverse)
		},
		{
			.name = "Bubble Sort Iterative (no nested for loops) Ordered",
			.fp = bubble_sort_optim,
			.clear_counters = bubble_clear_counters,
			.get_counters = bubble_get_counters,
			.input = ordered,
			.input_l = 0,
			.input_r = ITEMS_NUM - 1,
			.expected = expected,
			.data_size = sizeof(*ordered) * ITEMS_NUM,
			.elem_size = sizeof(*ordered)
		},
		// Bubble sort optimised iterative
		{
			.name = "Bubble Sort Optimised Iterative Random",
			.fp = bubble_sort_optim2,
			.clear_counters = bubble_clear_counters,
			.get_counters = bubble_get_counters,
			.input = random_data,
			.input_l = 0,
			.input_r = ITEMS_NUM - 1,
			.expected = expected,
			.data_size = sizeof(*random_data) * ITEMS_NUM,
			.elem_size = sizeof(*random_data)
		},
		{
			.name = "Bubble Sort Optimised Iterative Reverse",
			.fp = bubble_sort_optim2,
			.clear_counters = bubble_clear_counters,
			.get_counters = bubble_get_counters,
			.input = reverse,
			.input_l = 0,
			.input_r = ITEMS_NUM - 1,
			.expected = expected,
			.data_size = sizeof(*reverse) * ITEMS_NUM,
			.elem_size = sizeof(*reverse)
		},
		{
			.name = "Bubble Sort Optimised Iterative Ordered",
			.fp = bubble_sort_optim2,
			.clear_counters = bubble_clear_counters,
			.get_counters = bubble_get_counters,
			.input = ordered,
			.input_l = 0,
			.input_r = ITEMS_NUM - 1,
			.expected = expected,
			.data_size = sizeof(*ordered) * ITEMS_NUM,
			.elem_size = sizeof(*ordered)
		},
		// Shell sort
		{
			.name = "Shell Sort Iterative (h=3*h+1) Random",
			.fp = shell_sort,
			.clear_counters = shell_clear_counters,
			.get_counters = shell_get_counters,
			.input = random_data,
			.input_l = 0,
			.input_r = ITEMS_NUM - 1,
			.expected = expected,
			.data_size = sizeof(*random_data) * ITEMS_NUM,
			.elem_size = sizeof(*random_data)
		},
		{
			.name = "Shell Sort Iterative (h=3*h+1) Reverse",
			.fp = shell_sort,
			.clear_counters = shell_clear_counters,
			.get_counters = shell_get_counters,
			.input = reverse,
			.input_l = 0,
			.input_r = ITEMS_NUM - 1,
			.expected = expected,
			.data_size = sizeof(*reverse) * ITEMS_NUM,
			.elem_size = sizeof(*reverse)
		},
		{
			.name = "Shell Sort Iterative (h=3*h+1) Ordered",
			.fp = shell_sort,
			.clear_counters = shell_clear_counters,
			.get_counters = shell_get_counters,
			.input = ordered,
			.input_l = 0,
			.input_r = ITEMS_NUM - 1,
			.expected = expected,
			.data_size = sizeof(*ordered) * ITEMS_NUM,
			.elem_size = sizeof(*ordered)
		},
		// Insertion sort iterative
		{
			.name = "Insertion Sort Iterative Random",
			.fp = insertion_sort,
			.clear_counters = insertion_clear_counters,
			.get_counters = insertion_get_counters,
			.input = random_data,
			.input_l = 0,
			.input_r = ITEMS_NUM - 1,
			.expected = expected,
			.data_size = sizeof(*random_data) * ITEMS_NUM,
			.elem_size = sizeof(*random_data)
		},
		{
			.name = "Insertion Sort Iterative Reverse",
			.fp = insertion_sort,
			.clear_counters = insertion_clear_counters,
			.get_counters = insertion_get_counters,
			.input = reverse,
			.input_l = 0,
			.input_r = ITEMS_NUM - 1,
			.expected = expected,
			.data_size = sizeof(*reverse) * ITEMS_NUM,
			.elem_size = sizeof(*reverse)
		},
		{
			.name = "Insertion Sort Iterative Ordered",
			.fp = insertion_sort,
			.clear_counters = insertion_clear_counters,
			.get_counters = insertion_get_counters,
			.input = ordered,
			.input_l = 0,
			.input_r = ITEMS_NUM - 1,
			.expected = expected,
			.data_size = sizeof(*ordered) * ITEMS_NUM,
			.elem_size = sizeof(*ordered)
		},
		// Insertion sort iterative (pivot)
		{
			.name = "Insertion Sort Iterative (pivot) Random",
			.fp = insertion_sort_pivot,
			.clear_counters = insertion_clear_counters,
			.get_counters = insertion_get_counters,
			.input = random_data,
			.input_l = 0,
			.input_r = ITEMS_NUM - 1,
			.expected = expected,
			.data_size = sizeof(*random_data) * ITEMS_NUM,
			.elem_size = sizeof(*random_data)
		},
		{
			.name = "Insertion Sort Iterative (pivot) Reverse",
			.fp = insertion_sort_pivot,
			.clear_counters = insertion_clear_counters,
			.get_counters = insertion_get_counters,
			.input = reverse,
			.input_l = 0,
			.input_r = ITEMS_NUM - 1,
			.expected = expected,
			.data_size = sizeof(*reverse) * ITEMS_NUM,
			.elem_size = sizeof(*reverse)
		},
		{
			.name = "Insertion Sort Iterative (pivot) Ordered",
			.fp = insertion_sort_pivot,
			.clear_counters = insertion_clear_counters,
			.get_counters = insertion_get_counters,
			.input = ordered,
			.input_l = 0,
			.input_r = ITEMS_NUM - 1,
			.expected = expected,
			.data_size = sizeof(*ordered) * ITEMS_NUM,
			.elem_size = sizeof(*ordered)
		},
		// Quicksort recursive
		{
			.name = "Quicksort Recursive Random",
			.fp = quicksort,
			.clear_counters = quick_clear_counters,
			.get_counters = quick_get_counters,
			.input = random_data,
			.input_l = 0,
			.input_r = ITEMS_NUM - 1,
			.expected = expected,
			.data_size = sizeof(*random_data) * ITEMS_NUM,
			.elem_size = sizeof(*random_data)
		},
		{
			.name = "Quicksort Recursive Reverse",
			.fp = quicksort,
			.clear_counters = quick_clear_counters,
			.get_counters = quick_get_counters,
			.input = reverse,
			.input_l = 0,
			.input_r = ITEMS_NUM - 1,
			.expected = expected,
			.data_size = sizeof(*reverse) * ITEMS_NUM,
			.elem_size = sizeof(*reverse)
		},
		{
			.name = "Quicksort Recursive Ordered",
			.fp = quicksort,
			.clear_counters = quick_clear_counters,
			.get_counters = quick_get_counters,
			.input = ordered,
			.input_l = 0,
			.input_r = ITEMS_NUM - 1,
			.expected = expected,
			.data_size = sizeof(*ordered) * ITEMS_NUM,
			.elem_size = sizeof(*ordered)
		},
		// Quicksort recursive (median 3)
		{
			.name = "Quicksort (Median 3) Recursive Random",
			.fp = quicksort_median_3,
			.clear_counters = quick_clear_counters,
			.get_counters = quick_get_counters,
			.input = random_data,
			.input_l = 0,
			.input_r = ITEMS_NUM - 1,
			.expected = expected,
			.data_size = sizeof(*random_data) * ITEMS_NUM,
			.elem_size = sizeof(*random_data)
		},
		{
			.name = "Quicksort (Median 3) Recursive Reverse",
			.fp = quicksort_median_3,
			.clear_counters = quick_clear_counters,
			.get_counters = quick_get_counters,
			.input = reverse,
			.input_l = 0,
			.input_r = ITEMS_NUM - 1,
			.expected = expected,
			.data_size = sizeof(*reverse) * ITEMS_NUM,
			.elem_size = sizeof(*reverse)
		},
		{
			.name = "Quicksort (Median 3) Recursive Ordered",
			.fp = quicksort_median_3,
			.clear_counters = quick_clear_counters,
			.get_counters = quick_get_counters,
			.input = ordered,
			.input_l = 0,
			.input_r = ITEMS_NUM - 1,
			.expected = expected,
			.data_size = sizeof(*ordered) * ITEMS_NUM,
			.elem_size = sizeof(*ordered)
		},
		// quicksort recursive (median 3 shortest tail)
		{
			.name = "Quicksort (Median 3 shortest tail) Recursive Random",
			.fp = quicksort_median_3_short,
			.clear_counters = quick_clear_counters,
			.get_counters = quick_get_counters,
			.input = random_data,
			.input_l = 0,
			.input_r = ITEMS_NUM - 1,
			.expected = expected,
			.data_size = sizeof(*random_data) * ITEMS_NUM,
			.elem_size = sizeof(*random_data)
		},
		{
			.name = "Quicksort (Median 3 shortest tail) Recursive Reverse",
			.fp = quicksort_median_3_short,
			.clear_counters = quick_clear_counters,
			.get_counters = quick_get_counters,
			.input = reverse,
			.input_l = 0,
			.input_r = ITEMS_NUM - 1,
			.expected = expected,
			.data_size = sizeof(*reverse) * ITEMS_NUM,
			.elem_size = sizeof(*reverse)
		},
		{
			.name = "Quicksort (Median 3 shortest tail) Recursive Ordered",
			.fp = quicksort_median_3_short,
			.clear_counters = quick_clear_counters,
			.get_counters = quick_get_counters,
			.input = ordered,
			.input_l = 0,
			.input_r = ITEMS_NUM - 1,
			.expected = expected,
			.data_size = sizeof(*ordered) * ITEMS_NUM,
			.elem_size = sizeof(*ordered)
		}
	};

	for (size_t i = 0; i < ARRAY_SIZE(tests); i++) {
		int status = run_timed_test(&tests[i]);
		char test_success[] = "OK";
		char test_fail[] = "FAIL";
		char *test_status;
		if (status) {
			fprintf(stderr, "Test failed with status: %d\n", status);
		} else {
			test_status = (tests[i].status) ? test_fail : test_success;
			printf("%s (%f ms, %lu swaps, %lu comparisons, %lu calls) %s\n",
				tests[i].name,
				1e3f * (tests[i].time.tv_sec
					+ tests[i].time.tv_nsec / 1e9f),
				tests[i].cntrs.swps, tests[i].cntrs.cmps,
				tests[i].cntrs.calls, test_status);
		}
	}

	deallocate_int_arrays(arrays, ARRAY_SIZE(arrays));

	return 0;
}

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
	int *ordered = NULL;
	int *reverse = NULL;
	int *recursive = NULL;
	int *iterative = NULL;

	int **arrays[] = {&random_data, &ordered, &reverse, &recursive, &iterative};

	// Allocate all
	if (allocate_int_arrays(arrays, ARRAY_SIZE(arrays), ITEMS_NUM)) {
		printf("Allocation failure\n");
		deallocate_int_arrays(arrays, ARRAY_SIZE(arrays));
		return -1;
	}

	// Initialise random numbers
	printf("generating %d numbers\n", ITEMS_NUM);
	srand(0);
	for (int i = 0; i < ITEMS_NUM; i++) {
		random_data[i] = rand();
#ifdef DBGPRINT
		printf("%d\n", random_data[i]);
#endif
	}

	printf("initialising\n");
	memcpy(ordered, random_data, sizeof(*ordered)*ITEMS_NUM);

	printf("sorting\n");
	// sort the array using standard functions
	qsort(ordered, ITEMS_NUM, sizeof(*ordered), cmp_ints);

	printf("reversing\n");
	// reverse the sorted array
	for (int i = 0, j = ITEMS_NUM-1; i < ITEMS_NUM; i++, j--) {
		reverse[i] = ordered[j];
#ifdef DBGPRINT
		printf("%d\n", reverse[i]);
#endif
	}

	struct timed_test tests[] = {
		{
			.name = "Selection Sort Iterative Random",
			.fp = selection_sort,
			.input = random_data,
			.input_l = 0,
			.input_r = ITEMS_NUM-1,
			.output = iterative,
			.expected = ordered,
			.data_size = sizeof(*random_data)*ITEMS_NUM,
			.elem_size = sizeof(*random_data)
		},
		{
			.name = "Selection Sort Recursive Random",
			.fp = selection_sort_rec,
			.input = random_data,
			.input_l = 0,
			.input_r = ITEMS_NUM-1,
			.output = recursive,
			.expected = ordered,
			.data_size = sizeof(*random_data)*ITEMS_NUM,
			.elem_size = sizeof(*random_data)
		},
		{
			.name = "Selection Sort Iterative Reverse",
			.fp = selection_sort,
			.input = reverse,
			.input_l = 0,
			.input_r = ITEMS_NUM-1,
			.output = iterative,
			.expected = ordered,
			.data_size = sizeof(*reverse)*ITEMS_NUM,
			.elem_size = sizeof(*reverse)
		},
		{
			.name = "Selection Sort Recursive Reverse",
			.fp = selection_sort_rec,
			.input = reverse,
			.input_l = 0,
			.input_r = ITEMS_NUM-1,
			.output = recursive,
			.expected = ordered,
			.data_size = sizeof(*reverse)*ITEMS_NUM,
			.elem_size = sizeof(*reverse)
		},
		{
			.name = "Bubble Sort Iterative Random",
			.fp = bubble_sort,
			.input = random_data,
			.input_l = 0,
			.input_r = ITEMS_NUM-1,
			.output = iterative,
			.expected = ordered,
			.data_size = sizeof(*random_data)*ITEMS_NUM,
			.elem_size = sizeof(*random_data)
		},
		{
			.name = "Bubble Sort Iterative Reverse",
			.fp = bubble_sort,
			.input = reverse,
			.input_l = 0,
			.input_r = ITEMS_NUM-1,
			.output = iterative,
			.expected = ordered,
			.data_size = sizeof(*reverse)*ITEMS_NUM,
			.elem_size = sizeof(*reverse)
		},
		{
			.name = "Bubble Sort Recursive Random",
			.fp = bubble_sort_rec,
			.input = random_data,
			.input_l = 0,
			.input_r = ITEMS_NUM-1,
			.output = iterative,
			.expected = ordered,
			.data_size = sizeof(*random_data)*ITEMS_NUM,
			.elem_size = sizeof(*random_data)
		},
		{
			.name = "Bubble Sort Recursive Reverse",
			.fp = bubble_sort_rec,
			.input = reverse,
			.input_l = 0,
			.input_r = ITEMS_NUM-1,
			.output = iterative,
			.expected = ordered,
			.data_size = sizeof(*reverse)*ITEMS_NUM,
			.elem_size = sizeof(*reverse)
		},
		{
			.name = "Bubble Sort Iterative (no nested for loops) Random",
			.fp = bubble_sort_optim,
			.input = random_data,
			.input_l = 0,
			.input_r = ITEMS_NUM-1,
			.output = iterative,
			.expected = ordered,
			.data_size = sizeof(*random_data)*ITEMS_NUM,
			.elem_size = sizeof(*random_data)
		},
		{
			.name = "Bubble Sort Iterative (no nested for loops) Reverse",
			.fp = bubble_sort_optim,
			.input = reverse,
			.input_l = 0,
			.input_r = ITEMS_NUM-1,
			.output = iterative,
			.expected = ordered,
			.data_size = sizeof(*reverse)*ITEMS_NUM,
			.elem_size = sizeof(*reverse)
		},
		{
			.name = "Bubble Sort Optimised Iterative Random",
			.fp = bubble_sort_optim2,
			.input = random_data,
			.input_l = 0,
			.input_r = ITEMS_NUM-1,
			.output = iterative,
			.expected = ordered,
			.data_size = sizeof(*random_data)*ITEMS_NUM,
			.elem_size = sizeof(*random_data)
		},
		{
			.name = "Bubble Sort Optimised Iterative Reverse",
			.fp = bubble_sort_optim2,
			.input = reverse,
			.input_l = 0,
			.input_r = ITEMS_NUM-1,
			.output = iterative,
			.expected = ordered,
			.data_size = sizeof(*reverse)*ITEMS_NUM,
			.elem_size = sizeof(*reverse)
		},
		{
			.name = "Shell Sort Iterative (h=3*h+1) Random",
			.fp = shell_sort,
			.input = random_data,
			.input_l = 0,
			.input_r = ITEMS_NUM-1,
			.output = iterative,
			.expected = ordered,
			.data_size = sizeof(*random_data)*ITEMS_NUM,
			.elem_size = sizeof(*random_data)
		},
		{
			.name = "Shell Sort Iterative (h=3*h+1) Reverse",
			.fp = shell_sort,
			.input = reverse,
			.input_l = 0,
			.input_r = ITEMS_NUM-1,
			.output = iterative,
			.expected = ordered,
			.data_size = sizeof(*reverse)*ITEMS_NUM,
			.elem_size = sizeof(*reverse)
		},
		{
			.name = "Insertion Sort Iterative Random",
			.fp = insertion_sort,
			.input = random_data,
			.input_l = 0,
			.input_r = ITEMS_NUM-1,
			.output = iterative,
			.expected = ordered,
			.data_size = sizeof(*random_data)*ITEMS_NUM,
			.elem_size = sizeof(*random_data)
		},
		{
			.name = "Insertion Sort Iterative Reverse",
			.fp = insertion_sort,
			.input = reverse,
			.input_l = 0,
			.input_r = ITEMS_NUM-1,
			.output = iterative,
			.expected = ordered,
			.data_size = sizeof(*reverse)*ITEMS_NUM,
			.elem_size = sizeof(*reverse)
		},
		{
			.name = "Insertion Sort Iterative (pivot) Random",
			.fp = insertion_sort_pivot,
			.input = random_data,
			.input_l = 0,
			.input_r = ITEMS_NUM-1,
			.output = iterative,
			.expected = ordered,
			.data_size = sizeof(*random_data)*ITEMS_NUM,
			.elem_size = sizeof(*random_data)
		},
		{
			.name = "Insertion Sort Iterative (pivot) Reverse",
			.fp = insertion_sort_pivot,
			.input = reverse,
			.input_l = 0,
			.input_r = ITEMS_NUM-1,
			.output = iterative,
			.expected = ordered,
			.data_size = sizeof(*reverse)*ITEMS_NUM,
			.elem_size = sizeof(*reverse)
		},
		{
			.name = "Quicksort Recursive Random",
			.fp = quicksort,
			.input = random_data,
			.input_l = 0,
			.input_r = ITEMS_NUM-1,
			.output = iterative,
			.expected = ordered,
			.data_size = sizeof(*random_data)*ITEMS_NUM,
			.elem_size = sizeof(*random_data)
		},
		{
			.name = "Quicksort Recursive Reverse",
			.fp = quicksort,
			.input = reverse,
			.input_l = 0,
			.input_r = ITEMS_NUM-1,
			.output = iterative,
			.expected = ordered,
			.data_size = sizeof(*reverse)*ITEMS_NUM,
			.elem_size = sizeof(*reverse)
		},
		{
			.name = "Quicksort (Median 3) Recursive Random",
			.fp = quicksort_median_3,
			.input = random_data,
			.input_l = 0,
			.input_r = ITEMS_NUM-1,
			.output = iterative,
			.expected = ordered,
			.data_size = sizeof(*random_data)*ITEMS_NUM,
			.elem_size = sizeof(*random_data)
		},
		{
			.name = "Quicksort (Median 3) Recursive Reverse",
			.fp = quicksort_median_3,
			.input = reverse,
			.input_l = 0,
			.input_r = ITEMS_NUM-1,
			.output = iterative,
			.expected = ordered,
			.data_size = sizeof(*reverse)*ITEMS_NUM,
			.elem_size = sizeof(*reverse)
		},
		{
			.name = "Quicksort (Median 3 shortest tail) Recursive Random",
			.fp = quicksort_median_3_short,
			.input = random_data,
			.input_l = 0,
			.input_r = ITEMS_NUM-1,
			.output = iterative,
			.expected = ordered,
			.data_size = sizeof(*random_data)*ITEMS_NUM,
			.elem_size = sizeof(*random_data)
		},
		{
			.name = "Quicksort (Median 3 shortest tail) Recursive Reverse",
			.fp = quicksort_median_3_short,
			.input = reverse,
			.input_l = 0,
			.input_r = ITEMS_NUM-1,
			.output = iterative,
			.expected = ordered,
			.data_size = sizeof(*reverse)*ITEMS_NUM,
			.elem_size = sizeof(*reverse)
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
			printf("%s (%f ms) %s\n", tests[i].name,
					1e3f*(tests[i].time.tv_sec +
					tests[i].time.tv_nsec/1e9f), test_status);
		}
	}

	deallocate_int_arrays(arrays, ARRAY_SIZE(arrays));

	return 0;
}

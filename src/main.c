#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "selection_sort.h"
#include "bubble_sort.h"
#include "shell_sort.h"

#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

#define ITEMS_NUM (200000)

struct timed_test {
	char name[256];
	void (*fp)(int *v, size_t l, size_t r);
	int *input;
	size_t input_l;
	size_t input_r;
	int *output;
	int *expected;
	size_t data_size;
	size_t elem_size;
	int status;
	struct timespec time;
};

void timespec_diff(struct timespec *a, struct timespec *b, struct timespec *r)
{
	// from timersub macro on glibc/time/sys/time.h
	r->tv_sec = a->tv_sec - b->tv_sec;
	r->tv_nsec = a->tv_nsec - b->tv_nsec;
	// tv_nsec counts the ns elapsed since the last second
	if (r->tv_nsec < 0) {
		--r->tv_sec;
		r->tv_nsec += 1000000000L;
	}
}

double timespecdiff(struct timespec *a, struct timespec *b)
{
	struct timespec r;
	timespec_diff(a, b, &r);
	return r.tv_sec + r.tv_nsec/1e9;
}

float timespecdiff_f(struct timespec *a, struct timespec *b)
{
	struct timespec r;
	timespec_diff(a, b, &r);
	return r.tv_sec + r.tv_nsec/1e9f;
}


int cmp_ints(const void *i1, const void *i2)
{
	return (*(int *)i1)-(*(int *)i2);
}

int allocate_int_arrays(int ***arr, size_t alen, size_t len)
{
	for (size_t i = 0; i < alen; i++) {
		*arr[i] = calloc(sizeof(**arr), len);
		if (*arr[i] == NULL)
			return -1;
	}
	return 0;
}

void deallocate_int_arrays(int ***arr, size_t alen)
{
	for (size_t i = 0; i < alen; i++) {
		if (*arr[i] != NULL) {
			free(*arr[i]);
			*arr[i] = NULL;
		}
	}
}

int run_timed_test(struct timed_test *t)
{
	struct timespec tic, toc;

	if (t->name == NULL || t->fp == NULL || t->input == NULL || t->output == NULL
			|| t->expected == NULL || t->elem_size == 0)
		return -1;

#ifdef DBGPRINT
	printf("\nBefore initialisation\n");
	for (size_t i = 0; i < t->data_size/t->elem_size; i++)
		printf("input[%lu]=%d\toutput[%lu]=%d\texpected[%lu]=%d\n",
				i, t->input[i], i, t->output[i], i, t->expected[i]);
#endif

	fprintf(stderr, "Initialising test: %s\n", t->name);
	memcpy(t->output, t->input, t->data_size);
	fprintf(stderr, "Starting test: %s\n", t->name);

#ifdef DBGPRINT
	printf("\nAfter initialisation\n");
	for (size_t i = 0; i < t->data_size/t->elem_size; i++)
		printf("input[%lu]=%d\toutput[%lu]=%d\texpected[%lu]=%d\n",
				i, t->input[i], i, t->output[i], i, t->expected[i]);
#endif

	clock_gettime(CLOCK_MONOTONIC, &tic);
	t->fp(t->output, t->input_l, t->input_r);
	clock_gettime(CLOCK_MONOTONIC, &toc);

	timespec_diff(&toc, &tic, &t->time);
	t->status = memcmp(t->expected, t->output, t->data_size);

#ifdef DBGPRINT
	printf("\nResult\n");
	for (size_t i = 0; i < t->data_size/t->elem_size; i++)
		printf("input[%lu]=%d\toutput[%lu]=%d\texpected[%lu]=%d\n",
				i, t->input[i], i, t->output[i], i, t->expected[i]);
#endif
	return 0;
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

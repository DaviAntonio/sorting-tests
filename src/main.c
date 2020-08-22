#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "selection_sort.h"

#define ITEMS_NUM (200000)

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
		*arr[i] = calloc(sizeof(int *), len);
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

int main()
{
	int *random_data = NULL;
	int *ordered = NULL;
	int *reverse = NULL;
	int *recursive = NULL;
	int *iterative = NULL;

	int **arrays[5] = {&random_data, &ordered, &reverse, &recursive, &iterative};

	struct timespec tic, toc;
	float msdiff;

	// Allocate all
	if (allocate_int_arrays(arrays, 5, ITEMS_NUM)) {
		printf("Allocation failure\n");
		deallocate_int_arrays(arrays, 5);
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
	memcpy(ordered, random_data, ITEMS_NUM*sizeof(int));

	printf("sorting\n");
	// order the array using standard functions
	qsort(ordered, ITEMS_NUM, sizeof(int), cmp_ints);

	printf("reversing\n");
	// reverse the sorted array
	for (int i = 0, j = ITEMS_NUM-1; i < ITEMS_NUM; i++, j--) {
		reverse[i] = ordered[j];
#ifdef DBGPRINT
		printf("%d\n", reverse[i]);
#endif
	}

	// check
	printf("initialising iterative random\n");
	memcpy(iterative, random_data, ITEMS_NUM*sizeof(int));
	clock_gettime(CLOCK_MONOTONIC, &tic);
	selection_sort(iterative, 0, ITEMS_NUM-1);
	clock_gettime(CLOCK_MONOTONIC, &toc);
	msdiff = 1e3f*timespecdiff_f(&toc, &tic);
	if (!memcmp(iterative, ordered, ITEMS_NUM*sizeof(int)))
		printf("Iterative random (%f ms) OK\n", msdiff);
	else
		printf("Iterative random (%f ms) FAIL\n", msdiff);

	printf("initialising recursive random\n");
	memcpy(recursive, random_data, ITEMS_NUM*sizeof(int));
	clock_gettime(CLOCK_MONOTONIC, &tic);
	selection_sort_rec(recursive, 0, ITEMS_NUM-1);
	clock_gettime(CLOCK_MONOTONIC, &toc);
	msdiff = 1e3f*timespecdiff_f(&toc, &tic);
	if (!memcmp(recursive, ordered, ITEMS_NUM*sizeof(int)))
		printf("Recursive random (%f ms) OK\n", msdiff);
	else
		printf("Recursive random (%f ms) FAIL\n", msdiff);

	printf("initialising iterative reverse\n");
	memcpy(iterative, reverse, ITEMS_NUM*sizeof(int));
	clock_gettime(CLOCK_MONOTONIC, &tic);
	selection_sort(iterative, 0, ITEMS_NUM-1);
	clock_gettime(CLOCK_MONOTONIC, &toc);
	msdiff = 1e3f*timespecdiff_f(&toc, &tic);
	if (!memcmp(iterative, ordered, ITEMS_NUM*sizeof(int)))
		printf("Iterative reverse (%f ms) OK\n", msdiff);
	else
		printf("Iterative reverse (%f ms) FAIL\n", msdiff);

	printf("initialising recursive reverse\n");
	memcpy(recursive, reverse, ITEMS_NUM*sizeof(int));
	clock_gettime(CLOCK_MONOTONIC, &tic);
	selection_sort_rec(recursive, 0, ITEMS_NUM-1);
	clock_gettime(CLOCK_MONOTONIC, &toc);
	msdiff = 1e3f*timespecdiff_f(&toc, &tic);
	if (!memcmp(recursive, ordered, ITEMS_NUM*sizeof(int)))
		printf("Recursive reverse (%f ms) OK\n", msdiff);
	else
		printf("Recursive reverse (%f ms) FAIL\n", msdiff);

	deallocate_int_arrays(arrays, 5);
	return 0;
}

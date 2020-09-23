#include <string.h>
#include "shell_sort.h"
#include "int_arrays_sorting_macros.h"

static struct counters insertion_h;
static struct counters shell;

struct counters shell_get_counters(void (*fp)(void *, size_t, size_t))
{
	if (fp == shell_sort)
		return add_counters(shell, insertion_h);
	else
		return insertion_h;
}

void shell_clear_counters(void (*fp)(void *, size_t, size_t))
{
	memset(&insertion_h, 0, sizeof(insertion_h));
	memset(&shell, 0, sizeof(shell));
}

/* Insertion sort with configurable hop on array [l, r] */
static void insertion_sort_h(void *vin, size_t l, size_t r, size_t h)
{
	INIT_COUNTERS(insertion_h);
	ITEM *v = vin;
	for (size_t i = l + h; i <= r; i++) {
		size_t j = i;
		ITEM t = v[j];
		while (j >= l + h && LESS(t, v[j - h])) {
			v[j] = v[j - h];
			j -= h;
		}
		v[j] = t;
	}
}

void shell_sort(void *vin, size_t l, size_t r)
{
	INIT_COUNTERS(shell);
	COUNT_CALLS;
	ITEM *v = vin;
	size_t h;
	for (h = 1; h <= (r - l)/9; h = 3*h + 1);
	for (; h > 0; h = h/3)
		insertion_sort_h(v, l, r, h);
}

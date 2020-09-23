#include <stdbool.h>
#include <string.h>
#include "bubble_sort.h"
#include "int_arrays_sorting_macros.h"

static struct counters bubble;
static struct counters bubble_rec;
static struct counters bubble_optim;
static struct counters bubble_optim2;

struct counters bubble_get_counters(void (*fp)(void *, size_t, size_t))
{
	if (fp == bubble_sort)
		return bubble;
	else if (fp == bubble_sort_rec)
		return bubble_rec;
	else if (fp == bubble_sort_optim)
		return bubble_optim;
	else if (fp == bubble_sort_optim2)
		return bubble_optim2;
	else
		return bubble;
}

void bubble_clear_counters(void (*fp)(void *, size_t, size_t))
{
	if (fp == bubble_sort)
		memset(&bubble, 0, sizeof(bubble));
	else if (fp == bubble_sort_rec)
		memset(&bubble_rec, 0, sizeof(bubble_rec));
	else if (fp == bubble_sort_optim)
		memset(&bubble_optim, 0, sizeof(bubble_optim));
	else if (fp == bubble_sort_optim2)
		memset(&bubble_optim2, 0, sizeof(bubble_optim2));
}

void bubble_sort(void *vin, size_t l, size_t r)
{
	INIT_COUNTERS(bubble);
	COUNT_CALLS;

	ITEM *v = vin;
	for (size_t i = l; i < r; i++)
		for (size_t j = l; j < r; j++)
			SWAP_LESS(v[j+1], v[j]);
}

void bubble_sort_rec(void *vin, size_t l, size_t r)
{
	INIT_COUNTERS(bubble_rec);
	COUNT_CALLS;

	ITEM *v = vin;
	if (r == l) return;

	for (size_t i = l; i < r; i++)
		SWAP_LESS(v[i+1], v[i]);

	bubble_sort_rec(v, l, r-1);
}

void bubble_sort_optim(void *vin, size_t l, size_t r)
{
	INIT_COUNTERS(bubble_optim);
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

void bubble_sort_optim2(void *vin, size_t l, size_t r)
{
	INIT_COUNTERS(bubble_optim2);
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

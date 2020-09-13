#include <stdbool.h>
#include "bubble_sort.h"
#include "int_arrays_sorting_macros.h"

void bubble_sort(void *vin, size_t l, size_t r)
{
	ITEM *v = vin;
	for (size_t i = l; i < r; i++)
		for (size_t j = l; j < r; j++)
			SWAP_LESS(v[j+1], v[j]);
}

void bubble_sort_rec(void *vin, size_t l, size_t r)
{
	ITEM *v = vin;
	if (r == l) return;

	for (size_t i = l; i < r; i++)
		SWAP_LESS(v[i+1], v[i]);

	bubble_sort_rec(v, l, r-1);
}

void bubble_sort_optim(void *vin, size_t l, size_t r)
{
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

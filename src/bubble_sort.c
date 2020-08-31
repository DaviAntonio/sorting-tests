#include <stdbool.h>
#include "bubble_sort.h"

void bubble_sort(ITEM *v, size_t l, size_t r)
{
	for (size_t i = l; i < r; i++)
		for (size_t j = l; j < r; j++)
			CMPEXCH(v[j+1], v[j]);
}

void bubble_sort_rec(ITEM *v, size_t l, size_t r)
{
	if (r == l) return;

	for (size_t i = l; i < r; i++)
		CMPEXCH(v[i+1], v[i]);

	bubble_sort_rec(v, l, r-1);
}

void bubble_sort_optim(ITEM *v, size_t l, size_t r)
{
	bool inversion = true;

	while (inversion) {
		inversion = false;
		/* Must include the last position as it compares the current
		 * element with the previous one */
		for (size_t i = l+1; i <= r; i++) {
			if (LESS(v[i], v[i-1])) {
				EXCH(v[i], v[i-1]);
				inversion = true;
			}
		}
	}
}

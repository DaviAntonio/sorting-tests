#ifndef INSERTIONSORT_H_H
#define INSERTIONSORT_H_H

#include <stddef.h>
#include "counters.h"
#include "int_arrays_sorting_macros.h"

static struct counters insertionsort_h_cntrs;

/* Insertion sort with configurable hop on array [l, r] */
inline static void insertionsort_h(void *vin, size_t l, size_t r, size_t h)
{
	INIT_COUNTERS(insertionsort_h_cntrs);
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

#endif

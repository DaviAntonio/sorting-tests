#ifndef CORMEN_PARTITION_H
#define CORMEN_PARTITION_H

#include <stddef.h>
#include "counters.h"
#include "int_arrays_sorting_macros.h"

static struct counters partition_cntrs;

/* Partition function according to Cormen */
inline static size_t partition(void *vin, size_t l, size_t r)
{
	INIT_COUNTERS(partition_cntrs);
	ITEM *v = vin;
	/** Pivot element */
	ITEM c = v[r];

	/** Pivot's final position */
	size_t j = l;

	for (size_t k = l; k < r; k++) {
		if (LESSEQ(v[k], c)) {
			SWAP(v[k], v[j]);
			j++;
		}
	}

	SWAP(v[j], v[r]);

	return j;
}

#endif

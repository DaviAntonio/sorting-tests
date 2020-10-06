#ifndef MERGE2_H
#define MERGE2_H

#include <stdlib.h>
#include "counters.h"
#include "int_arrays_sorting_macros.h"

static struct counters merge2_cntrs;

inline static void merge2(void *vin, size_t l, size_t r1, size_t r2)
{
	INIT_COUNTERS(merge2_cntrs);

	ITEM *v = vin;

	size_t k = 0, i = l, j = r1 + 1;
	ITEM *v2 = malloc(sizeof(*v2) * (r2 - l + 1));
	if (v2 == NULL) return;

	while (i <= r1 && j <= r2) {
		if (LESSEQ(v[i], v[j]))
			v2[k++] = v[i++];
		else
			v2[k++] = v[j++];
	}

	while (i <= r1) v2[k++] = v[i++];
	while (j <= r2) v2[k++] = v[j++];

	for (i = l, k = 0; i <= r2; i++, k++)
		v[i] = v2[k];

	free(v2);
}

#endif

#ifndef INT_ARRAYS_SORTING_MACROS_H
#define INT_ARRAYS_SORTING_MACROS_H

#include "counters.h"

#define ITEM int
#define KEY(x) (x)
#define INIT_COUNTERS(x) struct counters *_c = &(x)
#define COUNT_CALLS ++_c->calls
#define LESS(x, y) ({++_c->cmps; (KEY(x) < KEY(y));})
#define LESSEQ(x, y) ({++_c->cmps; (KEY(x) <= KEY(y));})
#define SWAP(x, y) do {ITEM t = (x); (x) = (y); (y) = t; ++_c->swps;} while (0)
#define SWAP_LESS(x, y) do {if (LESS(x, y)) SWAP(x, y);} while (0)

#endif

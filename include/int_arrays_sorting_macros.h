#ifndef INT_ARRAYS_SORTING_MACROS_H
#define INT_ARRAYS_SORTING_MACROS_H

#define ITEM int
#define KEY(x) (x)
#define LESS(x, y) (KEY(x) < KEY(y))
#define LESSEQ(x, y) (KEY(x) <= KEY(y))
#define SWAP(x, y) do {ITEM t = x; x = y; y = t;} while (0)
#define SWAP_LESS(x, y) do {if (LESS(x, y)) SWAP(x, y);} while (0)

#endif

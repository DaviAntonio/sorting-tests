#ifndef QUICKSORT_H
#define QUICKSORT_H

#include <stddef.h>

#define ITEM int
#define KEY(A) (A)
#define LESS(A, B) (KEY(A) < KEY(B))
#define LESSEQ(x, y) (KEY(x) <= KEY(y))
#define SWAP(x, y) do {ITEM t = x; x = y; y = t;} while (0)
#define LESS_SWAP(x, y) do {if (LESS(x, y)) SWAP(x, y);} while (0)

/* Simple quicksort on array [l, r] */
void quicksort(ITEM *v, size_t l, size_t r);

#endif

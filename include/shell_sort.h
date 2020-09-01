#ifndef SHELL_SORT_H
#define SHELL_SORT_H

#include <stddef.h>

#define ITEM int
#define KEY(A) (A)
#define LESS(A, B) (KEY(A) < KEY(B))
#define EXCH(A, B) do{ITEM t = A; A = B; B = t;}while(0)
#define CMPEXCH(A, B) do{if (LESS(A, B)) EXCH(A, B);}while(0)

/* Iterative shell sort on array [l, r]
 * h=1, h=3*h+1, h<=N/9  from Sedgewick's Algorithms in C */
void shell_sort(ITEM *v, size_t l, size_t r);

#endif

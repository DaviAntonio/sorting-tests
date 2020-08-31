#ifndef BUBBLE_SORT_H
#define BUBBLE_SORT_H

#include <stddef.h>

#define ITEM int
#define KEY(A) (A)
#define LESS(A, B) (KEY(A) < KEY(B))
#define EXCH(A, B) do{ITEM t = A; A = B; B = t;}while(0)
#define CMPEXCH(A, B) do{if (LESS(A, B)) EXCH(A, B);}while(0)

/* Iterative bubble sort on array [l, r] */
void bubble_sort(ITEM *v, size_t l, size_t r);

/* Recursive bubble sort on array [l, r] */
void bubble_sort_rec(ITEM *v, size_t l, size_t r);

/* Iterative optimised bubble sort on array [l, r]
 * Changes the nested loops for one loop and a flag */
void bubble_sort_optim(ITEM *v, size_t l, size_t r);

#endif

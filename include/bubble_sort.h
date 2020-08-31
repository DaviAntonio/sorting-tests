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
 * The nested for loops are replaced by one for one loop and a while loop with
 * a flag */
void bubble_sort_optim(ITEM *v, size_t l, size_t r);

/* Iterative optimised bubble sort on array [l, r]
 * Bubble sort will always place one or more elements in the correct place in
 * the array in each iteration. This implementation avoids the evaluation of
 * elements that were already sorted in their correct places */
void bubble_sort_optim2(ITEM *v, size_t l, size_t r);

#endif

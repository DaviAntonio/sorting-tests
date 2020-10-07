#ifndef BUBBLESORT_ITER_WHILE
#define BUBBLESORT_ITER_WHILE

#include <stddef.h>
#include "counters.h"
#include "timed_test.h"

/* Gets timed test definitions */
struct timed_test_defs bubblesort_iter_while_get_test_defs();

/* Iterative optimised bubble sort on array [l, r]
 * The nested for loops are replaced by one for one loop and a while loop with
 * a flag */
void bubblesort_iter_while(void *vin, size_t l, size_t r);

#endif

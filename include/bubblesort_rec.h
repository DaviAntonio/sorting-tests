#ifndef BUBBLESORT_REC
#define BUBBLESORT_REC

#include <stddef.h>
#include "counters.h"
#include "timed_test.h"

/* Gets timed test definitions */
struct timed_test_defs bubblesort_rec_get_test_defs();

/* Clear the counters */
void bubblesort_rec_clear_counters();

/* Get the counters */
struct counters bubblesort_rec_get_counters();

/* Recursive bubble sort on array [l, r] */
void bubblesort_rec(void *vin, size_t l, size_t r);

#endif

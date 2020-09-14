#ifndef TIMING_H
#define TIMING_H

#include <time.h>

/**
 * Stores the subtraction of two struct timespecs (stores seconds and
 * nanoseconds) and record the adjusted result on another struct
 * The operation is r = a - b */
void timespec_diff(struct timespec *a, struct timespec *b, struct timespec *r);

/**
 * Subtracts two struct timespecs and converts the result of this operation,
 * a - b, to a double precision floating point represenying the elapsed time in
 * seconds */
double timespecdiff(struct timespec *a, struct timespec *b);

/**
 * Subtracts two struct timespecs and converts the result of this operation,
 * a - b, to a single precision floating point represenying the elapsed time in
 * seconds */
float timespecdiff_f(struct timespec *a, struct timespec *b);

#endif

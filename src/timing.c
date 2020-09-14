#include "timing.h"

void timespec_diff(struct timespec *a, struct timespec *b, struct timespec *r)
{
	// from timersub macro on glibc/time/sys/time.h
	r->tv_sec = a->tv_sec - b->tv_sec;
	r->tv_nsec = a->tv_nsec - b->tv_nsec;
	// tv_nsec counts the ns elapsed since the last second
	if (r->tv_nsec < 0) {
		--r->tv_sec;
		r->tv_nsec += 1000000000L;
	}
}

double timespecdiff(struct timespec *a, struct timespec *b)
{
	struct timespec r;
	timespec_diff(a, b, &r);
	return r.tv_sec + r.tv_nsec/1e9;
}

float timespecdiff_f(struct timespec *a, struct timespec *b)
{
	struct timespec r;
	timespec_diff(a, b, &r);
	return r.tv_sec + r.tv_nsec/1e9f;
}

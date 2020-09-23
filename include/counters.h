#ifndef COUNTERS_H
#define COUNTERS_H

struct counters {
	long unsigned int swps;
	long unsigned int cmps;
	long unsigned int calls;
};

struct counters add_counters(struct counters a, struct counters b);

#endif

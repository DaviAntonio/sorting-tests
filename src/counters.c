#include "counters.h"

struct counters add_counters(struct counters a, struct counters b)
{
	struct counters c;
	c.swps = a.swps + b.swps;
	c.cmps = a.cmps + b.cmps;
	c.calls = a.calls + b.calls;
	return c;
}

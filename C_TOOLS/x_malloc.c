#include "x_malloc.h"

void *x_malloc(size_t size)
{
	if (fail_after > 0 && num_alloc++ >= fail_after)
		return NULL;
	return malloc(size);
}

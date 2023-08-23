#ifndef X_MALLOC_H
# define X_MALLOC_H

#include <stdlib.h>

int fail_after;
int num_alloc;
//add to the global header of the project '# define malloc(x) x_malloc(x)
void *x_malloc(size_t size);

#endif
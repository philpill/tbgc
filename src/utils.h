#ifndef UTILS_H_
#define UTILS_H_

#include <stdio.h>

void utils_clamp(double *val, double min, double max);
void *utils_malloc(size_t size);
void *utils_calloc(size_t nitems, size_t size);
void *utils_realloc(void *ptr, size_t new_size );
	
#endif
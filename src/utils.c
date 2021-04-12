#include <stdio.h>
#include "utils.h"

void utils_clamp(double *val, double min, double max)
{
    *val = *val > max ? max : *val;
    *val = *val < min ? min : *val;
}

void *utils_malloc(size_t size)
{
    int res = malloc(size);
    if (res == NULL)
    {
        puts("malloc error: Memory not allocated");
        exit(1);
    }
    return res;
}

void *utils_calloc(size_t nitems, size_t size)
{
    int res = calloc(nitems, size);
    if (res == NULL)
    {
        puts("calloc error: Memory not allocated");
        exit(1);
    }
    return res;
}

void *utils_realloc(void *ptr, size_t new_size)
{
    ptr = realloc(ptr, new_size);
    if (ptr == NULL)
    {
        puts("realloc error: Memory not allocated");
        exit(1);
    }
    return ptr;
}
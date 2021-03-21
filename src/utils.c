#include "utils.h"

void utils_clamp(int *val, int min, int max)
{
    *val = *val > max ? max : *val; 
    *val = *val < min ? min : *val; 
}
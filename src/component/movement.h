#ifndef COMPONENT_MOVEMENT_H_
#define COMPONENT_MOVEMENT_H_

#include <SDL.h>

typedef struct 
{
    int id;

    double acc_x;
    double acc_y;
    double acc_max_x;
    double acc_min_x;
    double acc_max_y;
    double acc_min_y;

    double vel_x;
    double vel_y;
    double vel_max_x;
    double vel_min_x;
    double vel_max_y;
    double vel_min_y;

} MovementComponent; 

#endif
#ifndef COMPONENT_INPUT_H_
#define COMPONENT_INPUT_H_

#include <SDL.h>
#include <stdbool.h>

typedef struct 
{
    int id;
    bool up;
    bool down;
    bool left;
    bool right;
    bool jump;

} InputComponent; 

#endif
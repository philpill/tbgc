#ifndef SYSTEM_MOVEMENT_H_
#define SYSTEM_MOVEMENT_H_

#include <SDL.h>
#include "../manager/entity.h"

void system_movement_tick(Uint32 current);
int system_movement_init();

#endif
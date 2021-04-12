#ifndef SYSTEM_PHYSICS_H_
#define SYSTEM_PHYSICS_H_

#include <SDL.h>
#include "../manager/entity.h"

int system_physics_init();
void system_physics_tick(Uint32 current);

#endif
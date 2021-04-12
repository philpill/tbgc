#ifndef SYSTEM_RENDER_H_
#define SYSTEM_RENDER_H_

#include <SDL.h>
#include "../manager/entity.h"

void system_render_tick(Uint32 current);
int system_render_init();
void system_render_get_texture();

#endif
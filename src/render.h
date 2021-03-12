#ifndef RENDER_H_
#define RENDER_H_


#include <SDL.h>
#include "player.h"

int render_init(Uint32 start_t, Position *player_pos);
int render_tick(Uint32 current_t);
void render_destroy();

#endif
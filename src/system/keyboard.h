#ifndef SYSTEM_KEYBOARD_H_
#define SYSTEM_KEYBOARD_H_

#include <SDL.h>
#include "../manager/entity.h"

int system_keyboard_tick(Uint32 current);
int system_keyboard_init();

#endif
#ifndef SYSTEM_JOYPAD_H_
#define SYSTEM_JOYPAD_H_

#include <SDL.h>

int system_joypad_tick(Uint32 current);
int system_joypad_init();
int system_joypad_exit();

#endif
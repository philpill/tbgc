#include <SDL.h>
#include <stdio.h>
#include <stdbool.h>

#include "component/physics.h"
#include "manager/entity.h"
#include "system/keyboard.h"
#include "system/movement.h"
#include "system/physics.h"
#include "system/render.h"
#include "system/joypad.h"


void close()
{
    // render_destroy();
    SDL_Quit();
}

int main(int argc, char *argv[])
{
    bool        quit    = false;

    Uint32      start_t = SDL_GetTicks(), 
                current;

    manager_entity_init();

    system_keyboard_init();
    system_movement_init();
    system_physics_init();
    system_render_init();
    system_joypad_init();

    manager_entity_add_player_entity();

    while (!quit)
    {
        current = SDL_GetTicks();

        if (system_keyboard_tick(current) != 0)
        {
            quit = true;
        }
        system_movement_tick(current);
        system_physics_tick(current);
        system_render_tick(current);
        system_joypad_tick(current);
    }

    system_joypad_exit();

    close();

    return 0;
}

#include <SDL.h>
#include <stdio.h>
#include <stdbool.h>

#include "components/render.h"
#include "systems/event.h"
#include "systems/render.h"
#include "entities/player.h"

void close()
{
    s_render_destroy();
    SDL_Quit();
}

int main(int argc, char *args[])
{
    bool quit = false;

    Uint32 start_t, current_t;

    // start timer
    start_t = SDL_GetTicks();

    PlayerEntity player_entity;

    //render_system_add_component(&(player_entity.render_component));

    s_render_init();
    s_event_init();

    while (!quit)
    {
        current_t = SDL_GetTicks();

        if (s_event_tick() != 0)
        {
            quit = true;
        }

        s_render_tick();
    }

    close();

    return 0;
}

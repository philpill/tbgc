#include <SDL.h>
#include <stdio.h>
#include <stdbool.h>

#include "event.h"
#include "player.h"
#include "components/render.h"
#include "systems/render.h"
#include "entities/player.h"

void close()
{
    render_destroy();
    render_system_destroy();
    SDL_Quit();
}

int main(int argc, char *args[])
{
    bool quit = false;

    Uint32 start_t, current_t;

    // start timer
    start_t = SDL_GetTicks();

    PlayerEntity player_entity;

    render_system_add_component(&(player_entity.render_component));

    render_system_init();

    while (!quit)
    {
        current_t = SDL_GetTicks();

        if (event_tick() != 0)
        {
            quit = true;
        }

        render_system_tick();
    }

    close();

    return 0;
}

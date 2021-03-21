#include <SDL.h>
#include <stdio.h>
#include <stdbool.h>

#include "event.h"
#include "player.h"
#include "level.h"

void close()
{
    render_destroy();
    SDL_Quit();
}

int main(int argc, char *argv[])
{
    bool        quit    = false;

    Uint32      start_t = SDL_GetTicks(), 
                current;
                
    Position        *player_pos;
    PlayerAction    *player_action;

    player_init(&player_pos, &player_action);
    render_init(start_t, player_pos, player_action);
    level_init();

    while (!quit)
    {
        current = SDL_GetTicks();

        if (event_tick() != 0)
        {
            quit = true;
        }

        player_tick(current);
        render_tick(current);
        level_tick();
    }

    close();

    return 0;
}

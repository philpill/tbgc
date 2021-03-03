#include <SDL.h>
#include <stdio.h>
#include <stdbool.h>

#include "event.h"
#include "player.h"

void close()
{
    render_destroy();
    SDL_Quit();
}

int main(int argc, char *args[])
{
    bool        quit    = false;

    Uint32      start_t = SDL_GetTicks(), 
                current;
                
    Position        *player_pos;
    PlayerAction    *player_action;

    player_init(&player_pos, &player_action);
    render_init(start_t, player_pos, player_action);

    while (!quit)
    {
        current = SDL_GetTicks();

        if (event_tick() != 0)
        {
            quit = true;
        }

        player_tick(current);
        render_tick(current);
    }

    close();

    return 0;
}

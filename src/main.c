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
    bool quit = false;

    Uint32 start_t, current_t;

    Position *player_pos;

    // start timer
    start_t = SDL_GetTicks();

    player_init(&player_pos);
    render_init(start_t, player_pos);

    while (!quit)
    {
        current_t = SDL_GetTicks();

        if (event_tick() != 0)
        {
            quit = true;
        }

        player_tick(current_t);
        render_tick(current_t);
    }

    close();

    return 0;
}

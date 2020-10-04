#include <SDL.h>
#include <stdio.h>
#include <stdbool.h>

#include "event.h"
#include "player.h"

const int SCREEN_TICK_PER_FRAME = 1000 / 30;

void close()
{
    render_destroy();
    SDL_Quit();
}

int main(int argc, char *args[])
{
    bool quit = false;

    double start_t, end_t, total_t;

    int posx = 0;
    int posy = 0;

    render_init();

    // start timer
    start_t = SDL_GetTicks();

    position player_pos = { 0, 0 };

    while (!quit)
    {
        if (event_handle() != 0) 
        {
            quit = true;
        }        

        player_handle(&player_pos);

        printf("charlie: %d\n", player_pos.x);

        render_handle(&player_pos);

        end_t = SDL_GetTicks();

        total_t = end_t - start_t;

        if (total_t < SCREEN_TICK_PER_FRAME)
        {
            SDL_Delay(SCREEN_TICK_PER_FRAME - total_t);

            start_t = SDL_GetTicks();
        }
    }

    close();

    return 0;
}

#include <stdbool.h>
#include <SDL.h>
#include "player.h"

static SDL_Event e;

int event_init()
{
}

int event_tick()
{
    while (SDL_PollEvent(&e) != 0)
    {
        if (e.type == SDL_QUIT)
        {
            return -1;
        }
    }

    const Uint8* keystates = SDL_GetKeyboardState(NULL);

     if (keystates[SDL_SCANCODE_ESCAPE]) {
        return -1;
    }   

    if (keystates[SDL_SCANCODE_LEFT]) {
        player_acc_x(-7);
    }

    if (keystates[SDL_SCANCODE_RIGHT]) {
        player_acc_x(7);
    }

    if (keystates[SDL_SCANCODE_SPACE]) {
        player_acc_y(7);
    }

    return 0;
}

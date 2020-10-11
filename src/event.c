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
        else if (e.type == SDL_KEYDOWN)
        {
            //Select surfaces based on key press
            switch (e.key.keysym.sym)
            {
            case SDLK_UP:
                // posy--;
                break;

            case SDLK_DOWN:
                // posy++;
                break;

            case SDLK_LEFT:
                player_accelerate_x(-7);
                break;

            case SDLK_RIGHT:
                player_accelerate_x(7);
                break;

            case SDLK_ESCAPE:
                return -1;
            }
        }
    }

    return 0;
}
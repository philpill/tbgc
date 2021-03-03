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

    if (keystates[SDL_SCANCODE_ESCAPE]) { return -1; }   



    if (keystates[SDL_SCANCODE_DOWN])
    { 
        player_crouch(); 
    } 
    else 
    {
        player_default();
    }


    if (keystates[SDL_SCANCODE_LEFT])   { player_backward(); }
    if (keystates[SDL_SCANCODE_RIGHT])  { player_forward(); }
    if (keystates[SDL_SCANCODE_SPACE])  { player_jump(); }

    return 0;
}

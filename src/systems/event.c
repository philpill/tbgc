#include <stdbool.h>
#include <SDL.h>

#include "event.h";
#include "../components/render.h";

static SDL_Event e;

static RenderComponent *components[100];
static int num_component = 0;

static void accelarate_components_x(int acc)
{
    for (int i = 0; i < num_component; i++)
    {
        components[i]->position.x += acc;
    }
}

int s_event_init()
{

}

void s_event_add_component(RenderComponent *component)
{
    components[num_component] = component;

    num_component++;
}

int s_event_tick()
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
                break;

            case SDLK_DOWN:
                break;

            case SDLK_LEFT:
                // player_accelerate_x(-7);
                accelarate_components_x(-7);
                break;

            case SDLK_RIGHT:
                // player_accelerate_x(7);
                accelarate_components_x(7);
                break;

            case SDLK_ESCAPE:
                return -1;
            }
        }
    }

    return 0;
}
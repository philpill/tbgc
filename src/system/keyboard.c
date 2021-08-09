#include <SDL.h>
#include "../manager/entity.h"
#include "../component/input.h"

static int system_mask = 8;

static SDL_Event e;

int system_keyboard_init()
{
    puts("system_keyboard_init");
}

int system_keyboard_tick(Uint32 current)
{
    while (SDL_PollEvent(&e) != 0)
    {
        if (e.type == SDL_QUIT)
        {
            return -1;
        }
    }

    const Uint8 *keystates = SDL_GetKeyboardState(NULL);

    if (keystates[SDL_SCANCODE_ESCAPE])
    {
        return -1;
    }

    if (keystates[SDL_SCANCODE_DOWN])
    {
        // player_crouch();
    }
    else
    {
        // player_default();
    }

    if (keystates[SDL_SCANCODE_LEFT])
    {
        // player_backward();
    }
    if (keystates[SDL_SCANCODE_RIGHT])
    {
        // player_forward();
    }
    if (keystates[SDL_SCANCODE_SPACE])
    {
        // player_jump();
    }

    Entity *entities = manager_entity_get_entities();
    int num_entities = manager_entity_get_num_entities();

    // printf("system_keyboard_tick: %p \n", entities);
    // printf("system_keyboard_tick: %d \n", entities[0].component_mask);

    // loop over entities
    for (int i = 0; i < num_entities; i++)
    {
        // get entities with relevant components
        if (entities[i].component_mask & system_mask > 0)
        {
            InputComponent *i_cmp = entities[i].cmp_input;

            i_cmp->up       = keystates[SDL_SCANCODE_UP];
            i_cmp->down     = keystates[SDL_SCANCODE_DOWN];
            // i_cmp->left     = keystates[SDL_SCANCODE_LEFT];
            // i_cmp->right    = keystates[SDL_SCANCODE_RIGHT];
            i_cmp->jump     = keystates[SDL_SCANCODE_SPACE];
        }
    }

    return 0;
}

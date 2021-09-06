#include <SDL.h>
#include "../manager/entity.h"

static int system_mask = 8;

static SDL_Event e;

static SDL_GameController *controller = NULL;

int system_joypad_init()
{
    puts("system_joypad_init");

    SDL_Init(SDL_INIT_GAMECONTROLLER);

    if (SDL_NumJoysticks() < 1)
    {
        printf("Warning: No joypads connected!\n");
    }
    else
    {
        //Load joystick
        controller = SDL_GameControllerOpen(0);
        if (controller == NULL)
        {
            printf("Warning: Unable to open game controller! SDL Error: %s\n", SDL_GetError());
        }
        SDL_GameControllerEventState(SDL_ENABLE);
    }
}

int system_joypad_tick(Uint32 current)
{
    if (SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_A))
    {
        printf("A\n");
    }

    if (SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_B))
    {
        printf("B\n");
    }

    if (SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_X))
    {
        printf("X\n");
    }

    if (SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_Y))
    {
        printf("Y\n");
    }

    if (SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_DPAD_UP))
    {
        printf("UP\n");
    }

    if (SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_DPAD_DOWN))
    {
        printf("DOWN\n");
    }

    if (SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_DPAD_LEFT))
    {
        printf("LEFT\n");
    }

    if (SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_DPAD_RIGHT))
    {
        printf("RIGHT\n");
    }

    Entity *entities = manager_entity_get_entities();
    int num_entities = manager_entity_get_num_entities();

    for (int i = 0; i < num_entities; i++)
    {
        if (entities[i].component_mask & system_mask > 0)
        {
            InputComponent *i_cmp = entities[i].cmp_input;

            // i_cmp->up       = keystates[SDL_SCANCODE_UP];
            // i_cmp->down     = keystates[SDL_SCANCODE_DOWN];
            // i_cmp->left =   SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_DPAD_LEFT);
            // i_cmp->right =  SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_DPAD_RIGHT);
            // i_cmp->jump     = keystates[SDL_SCANCODE_SPACE];
        }
    }

    return 0;
}

int system_joypad_exit()
{
    SDL_GameControllerClose(controller);
    controller = NULL;
}
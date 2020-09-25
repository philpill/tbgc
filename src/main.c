#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <stdbool.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main(int argc, char *args[])
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("init error: SDL_Error: %s\n", SDL_GetError());
    }
    else
    {
        SDL_Window *window = NULL;
        SDL_Surface *surface = NULL;

        bool quit = false;
        SDL_Event e;

        window = SDL_CreateWindow("TBGC", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

        if (window == NULL)
        {

            printf("create window error: SDL_Error: %s\n", SDL_GetError());
        }
        else
        {
            while (!quit)
            {
                while (SDL_PollEvent(&e) != 0)
                {
                    if (e.type == SDL_QUIT)
                    {
                        quit = true;
                    }
                }

                surface = SDL_GetWindowSurface(window);
                SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 0xFF, 0xFF, 0xFF));
                SDL_UpdateWindowSurface(window);
            }

            SDL_DestroyWindow(window);
            SDL_Quit();

            return 0;
        }
    }
}

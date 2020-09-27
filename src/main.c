#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <stdbool.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

const int SCREEN_TICK_PER_FRAME = 1000 / 30;

SDL_Window *window = NULL;
SDL_Surface *screenSurface = NULL;
SDL_Surface *pngSurface = NULL;

bool init()
{
    bool success = true;

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("init error: SDL_Error: %s\n", SDL_GetError());
        success = false;
    }
    else
    {
        window = SDL_CreateWindow("TBGC", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (window == NULL)
        {
            printf("create window error: SDL_Error: %s\n", SDL_GetError());
            success = false;
        }
        else
        {
            //Initialize PNG loading
            int imgFlags = IMG_INIT_PNG;
            if (!(IMG_Init(imgFlags) & imgFlags))
            {
                printf("SDL_image Error: %s\n", IMG_GetError());
                success = false;
            }
            else
            {
                screenSurface = SDL_GetWindowSurface(window);
            }
        }
    }

    return success;
}

void close()
{
    SDL_FreeSurface(pngSurface);
    pngSurface = NULL;

    SDL_DestroyWindow(window);
    window = NULL;

    IMG_Quit();
    SDL_Quit();
}

SDL_Surface *loadSurface(char *path)
{
    SDL_Surface *optimisedSurface = NULL;

    SDL_Surface *loadedSurface = IMG_Load(path);
    if (loadedSurface == NULL)
    {
        printf("Unable to load image. SDL_image Error: %s\n", IMG_GetError());
    }
    else
    {
        optimisedSurface = SDL_ConvertSurface(loadedSurface, screenSurface->format, 0);
        if (optimisedSurface == NULL)
        {
            printf("Unable to optimise image. SDL_image Error: %s\n", IMG_GetError());
        }

        SDL_FreeSurface(loadedSurface);
    }

    return optimisedSurface;
}

bool loadMedia()
{
    bool success = true;

    //Load PNG surface
    pngSurface = loadSurface("assets/1.png");
    if (pngSurface == NULL)
    {
        printf("Failed to load PNG image!\n");
        success = false;
    }

    return success;
}

int main(int argc, char *args[])
{
    if (!init())
    {
        printf("Failed to initialize!\n");
    }
    else
    {
        if (!loadMedia())
        {
            printf("Failed to load media!\n");
        }
        else
        {
            bool quit = false;
            SDL_Event e;

            Uint32 start_t, end_t, total_t;

            // start timer
            start_t = SDL_GetTicks();

            while (!quit)
            {
                while (SDL_PollEvent(&e) != 0)
                {
                    if (e.type == SDL_QUIT)
                    {
                        quit = true;
                    }
                }

                SDL_BlitSurface(pngSurface, NULL, screenSurface, NULL);

                SDL_UpdateWindowSurface(window);

                end_t = SDL_GetTicks();

                total_t = end_t - start_t;

                if (total_t < SCREEN_TICK_PER_FRAME)
                {
                    printf("%d\n", SDL_GetTicks());

                    SDL_Delay(SCREEN_TICK_PER_FRAME - total_t);

                    start_t = SDL_GetTicks();
                }
            }
        }
    }

    close();

    return 0;
}
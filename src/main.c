#include <SDL.h>
#include <stdio.h>
#include <stdbool.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

const int SCREEN_TICK_PER_FRAME = 1000 / 30;

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
SDL_Surface *screenSurface = NULL;
SDL_Surface *pngSurface = NULL;
SDL_Texture *pngTexture = NULL;
unsigned char *stbiData = NULL;

void close()
{
    SDL_DestroyTexture(pngTexture);
    pngTexture = NULL;

    SDL_DestroyRenderer(renderer);
    renderer = NULL;

    SDL_DestroyWindow(window);
    window = NULL;

    SDL_Quit();
}

int main(int argc, char *args[])
{
    bool quit = false;
    SDL_Event e;

    double start_t, end_t, total_t;

    SDL_Init(SDL_INIT_VIDEO);

    window = SDL_CreateWindow("TBGC", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    screenSurface = SDL_GetWindowSurface(window);

    int posx = 0;
    int posy = 0;

    int width, height, orig_format;
    int req_format = STBI_rgb_alpha;
    stbiData = stbi_load("assets/1.png", &width, &height, &orig_format, req_format);

    Uint32 rmask, gmask, bmask, amask;
    #if SDL_BYTEORDER == SDL_BIG_ENDIAN
        int shift = (req_format == STBI_rgb) ? 8 : 0;
        rmask = 0xff000000 >> shift;
        gmask = 0x00ff0000 >> shift;
        bmask = 0x0000ff00 >> shift;
        amask = 0x000000ff >> shift;
    #else // little endian, like x86
        rmask = 0x000000ff;
        gmask = 0x0000ff00;
        bmask = 0x00ff0000;
        amask = (req_format == STBI_rgb) ? 0 : 0xff000000;
    #endif

    int depth, pitch;
    if (req_format == STBI_rgb) {
        depth = 24;
        pitch = 3*width; // 3 bytes per pixel * pixels per row
    } else { // STBI_rgb_alpha (RGBA)
        depth = 32;
        pitch = 4*width;
    }

    // printf("width: %d\n", width);
    // printf("height: %d\n", height);

    pngSurface = SDL_CreateRGBSurfaceFrom((void*)stbiData, width, height, depth, pitch,
                                            rmask, gmask, bmask, amask);

    stbi_image_free(stbiData);
    stbiData = NULL;

    pngTexture = SDL_CreateTextureFromSurface(renderer, pngSurface);

    SDL_FreeSurface(pngSurface);
    pngSurface = NULL;

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
            else if (e.type == SDL_KEYDOWN)
            {
                //Select surfaces based on key press
                switch (e.key.keysym.sym)
                {
                case SDLK_UP:
                    posy--;
                    break;

                case SDLK_DOWN:
                    posy++;
                    break;

                case SDLK_LEFT:
                    posx--;
                    break;

                case SDLK_RIGHT:
                    posx++;
                    break;

                case SDLK_ESCAPE:
                    close();
                    return 0;
                }
            }
        }

        SDL_Rect dst;
        dst.x = posx;
        dst.y = posy;
        dst.w = 32;
        dst.h = 32;

        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, pngTexture, NULL, &dst);
        SDL_RenderPresent(renderer);

        end_t = SDL_GetTicks();

        total_t = end_t - start_t;

        // printf("%d - %d = %d\n", end_t, start_t, total_t);

        if (total_t < SCREEN_TICK_PER_FRAME)
        {
            // printf("delay: %d\n", SCREEN_TICK_PER_FRAME - total_t);

            SDL_Delay(SCREEN_TICK_PER_FRAME - total_t);

            start_t = SDL_GetTicks();
        }
    }

    close();

    return 0;
}

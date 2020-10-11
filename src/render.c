#include <SDL.h>
#include "player.h"
#include "utils.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

static SDL_Renderer *renderer = NULL;
static SDL_Texture *pngTexture = NULL;
static SDL_Rect srcRect, dstRect;
static SDL_Window *window = NULL;
static Position *player_position;

static int current_frame = 0;
static int animation_rate = 150;
static Uint32 start, delta;

static int loadImage()
{
    SDL_Surface *pngSurface = NULL;

    unsigned char *stbiData = NULL;

    int width, height, orig_format;
    int req_format = STBI_rgb_alpha;
    stbiData = stbi_load("assets/2.png", &width, &height, &orig_format, req_format);

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
    if (req_format == STBI_rgb)
    {
        depth = 24;
        pitch = 3 * width; // 3 bytes per pixel * pixels per row
    }
    else
    { // STBI_rgb_alpha (RGBA)
        depth = 32;
        pitch = 4 * width;
    }

    pngSurface = SDL_CreateRGBSurfaceFrom((void *)stbiData, width, height, depth, pitch,
                                          rmask, gmask, bmask, amask);

    stbi_image_free(stbiData);
    stbiData = NULL;

    pngTexture = SDL_CreateTextureFromSurface(renderer, pngSurface);

    SDL_FreeSurface(pngSurface);
    pngSurface = NULL;
}

int render_init(Uint32 start_t, Position *player_pos)
{
    player_position = player_pos;

    start = start_t;

    const int SCREEN_WIDTH = 640;
    const int SCREEN_HEIGHT = 480;

    SDL_Surface *screenSurface = NULL;

    SDL_Init(SDL_INIT_VIDEO);

    window = SDL_CreateWindow("TBGC", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    screenSurface = SDL_GetWindowSurface(window);

    loadImage();

    return 0;
}

// http://gamedevgeek.com/tutorials/animating-sprites-with-sdl/

int render_tick(Uint32 current_t)
{
    delta = current_t - start;

    if (delta > animation_rate)
    {
        current_frame = current_frame < 2 ? current_frame + 1 : 1;
        current_frame = dstRect.x == player_position->x ? 0 : current_frame;
        start = SDL_GetTicks();
    }

    srcRect.x = current_frame * 32;
    srcRect.y = 0;
    srcRect.w = 32;
    srcRect.h = 32;

    dstRect.x = player_position->x;
    dstRect.y = player_position->y;
    dstRect.w = 32;
    dstRect.h = 32;

    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, pngTexture, &srcRect, &dstRect);
    SDL_RenderPresent(renderer);
}

void render_destroy()
{
    SDL_DestroyTexture(pngTexture);
    pngTexture = NULL;

    SDL_DestroyRenderer(renderer);
    renderer = NULL;

    SDL_DestroyWindow(window);
    window = NULL;
}

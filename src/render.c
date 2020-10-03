#include <SDL.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

static SDL_Renderer *renderer = NULL;
static SDL_Texture *pngTexture = NULL;
static SDL_Window *window = NULL;

static int loadImage() {

    SDL_Surface *pngSurface = NULL;
    
    unsigned char *stbiData = NULL;

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
}

int render_init() {

    const int SCREEN_WIDTH = 640;
    const int SCREEN_HEIGHT = 480;

    SDL_Surface *screenSurface = NULL;

    SDL_Init(SDL_INIT_VIDEO);

    window = SDL_CreateWindow("TBGC", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    screenSurface = SDL_GetWindowSurface(window);

    loadImage();

    return 0;
}

int render_handle(int posx, int posy) {

    SDL_Rect dst;
    dst.x = posx;
    dst.y = posy;
    dst.w = 32;
    dst.h = 32;

    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, pngTexture, NULL, &dst);
    SDL_RenderPresent(renderer);
}

void render_destroy() {
    SDL_DestroyTexture(pngTexture);
    pngTexture = NULL;

    SDL_DestroyRenderer(renderer);
    renderer = NULL;

    SDL_DestroyWindow(window);
    window = NULL;
}

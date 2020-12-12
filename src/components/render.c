#include <SDL.h>
#include <string.h>
#include "../stb_image.h"
#include "component.h"
#include "render.h"

ComponentType type = RENDER;

static void get_surface(int width, int height, int orig_format, int req_format, char *stbiData, SDL_Surface **surf)
{
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

    SDL_Surface *surface = SDL_CreateRGBSurfaceFrom((void *)stbiData, width, height, depth, pitch,
                                                    rmask, gmask, bmask, amask);

    printf("surface: %p\n", (void *)&surface);

    *surf = surface;
}

void render_comp_loadImage(RenderComponent *component)
{
    SDL_Surface *surf = NULL;
    SDL_Texture *tex = NULL;
    unsigned char *stbiData = NULL;
    int width, height, orig_format;
    int req_format = STBI_rgb_alpha;

    printf("%s\n", component->resource_path);

    stbiData = stbi_load(component->resource_path, &width, &height, &orig_format, req_format);

    if (stbiData == NULL) { printf("NULL: %s\n", stbi_failure_reason()); return; }

    // debug surf address

    printf("surf1: %p\n", (void *)&surf);

    get_surface(width, height, orig_format, req_format, stbiData, &surf);

    printf("surf2: %p\n", (void *)&surf);

    stbi_image_free(stbiData);
    stbiData = NULL;

    if (surf == NULL) { fprintf(stderr, "get_surface failed: %s\n", SDL_GetError()); exit(1); }

    tex = SDL_CreateTextureFromSurface(component->renderer, surf);

    if (tex == NULL) { fprintf(stderr, "CreateTextureFromSurface failed: %s\n", SDL_GetError()); exit(1); }

    component->texture = tex;
    SDL_FreeSurface(surf);
    surf = NULL;
}

void render_comp_destroy(RenderComponent *component)
{
    SDL_DestroyTexture(component->texture);
    component->texture = NULL;

    // only pointer is cleared
    // actual destroy is only done by main
    component->renderer = NULL;
}
#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include "player.h"
#include "utils.h"
#include "render.h"
#include "asset.h" 

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

static Uint32 depth,
    start,
    delta,
    rmask,
    gmask,
    bmask,
    amask;

static int req_format = STBI_rgb_alpha,
           animation_rate = 150,
           num_components = 0,
           size_components = 0;

static SDL_Renderer *rndr = NULL;
static SDL_Window *wnd = NULL;
static Position *pos = NULL;
static PlayerAction *action = NULL;
static RenderComponent *components;

static SDL_Texture *get_texture_by_path(char *path)
{
    static unsigned char *stbiData = NULL;
    SDL_Texture *tex = NULL;
    SDL_Surface *srfc = NULL;
    int pitch,
        width,
        height,
        orig_format;

    if (!asset_does_file_exist(components[num_components].path))
    {
        printf("Error: File does not exist: %s\n", components[num_components].path);
        return NULL;
    }

    stbiData = stbi_load(path, &width, &height, &orig_format, req_format);
    pitch = 4 * width;

    srfc = SDL_CreateRGBSurfaceFrom((void *)stbiData, width, height, depth, pitch, rmask, gmask, bmask, amask);
    if (srfc == NULL)
    {
        printf("SDL_CreateRGBSurfaceFrom: %s\n", SDL_GetError());
        exit(1);
    }

    tex = SDL_CreateTextureFromSurface(rndr, srfc);
    if (tex == NULL)
    {
        printf("SDL_CreateTextureFromSurface: %s\n", SDL_GetError());
        exit(1);
    }

    SDL_FreeSurface(srfc);

    srfc = NULL;
    stbiData = NULL;

    return tex;
} 

int render_init(Uint32 start_t, Position *player_pos, PlayerAction *player_action)
{
    SDL_Surface *scrnSrfc = NULL;

    const int SCREEN_WIDTH = 640,
              SCREEN_HEIGHT = 480;

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
    amask = 0xff000000;
#endif

    depth = 32;

    pos = player_pos;
    action = player_action;
    start = start_t;

    SDL_Init(SDL_INIT_VIDEO);

    wnd = SDL_CreateWindow("TBGC", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (wnd == NULL)
    {
        printf("SDL_CreateWindow: %s\n", SDL_GetError());
        exit(1);
    }
    rndr = SDL_CreateRenderer(wnd, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (rndr == NULL)
    {
        printf("SDL_CreateRenderer: %s\n", SDL_GetError());
        exit(1);
    }
    scrnSrfc = SDL_GetWindowSurface(wnd);
    if (scrnSrfc == NULL)
    {
        printf("SDL_GetWindowSurface: %s\n", SDL_GetError());
        exit(1);
    }

    // create player component
    render_add_new_component("assets/2.png");
    return 0;
}

RenderComponent **render_get_components()
{
    return components;
}

RenderComponent *render_get_component_by_path(char *path)
{
    RenderComponent *component = malloc(sizeof(RenderComponent));
    if (component == NULL)
    {
        printf("Error: Memory not allocated\n");
        exit(1);
    }

    for (int i = 0; i < num_components; i++)
    {
        if (components[i].path != NULL && strcmp(components[i].path, path) == 0)
        {
            component = &components[i];
            break;
        }
    }

    return component;
}

RenderComponent *render_get_component_by_index(int index)
{
    RenderComponent *component = NULL;

    if (components[index].path != NULL)
    {
        component = malloc(sizeof(RenderComponent));
        if (component == NULL)
        {
            printf("Error: Memory not allocated\n");
            exit(1);
        }

        component = &components[index];
    }

    return component;
}

static void mem_check()
{
    if (size_components == 0)
    {
        size_components = 10;
        components = calloc(size_components, sizeof(RenderComponent));
        if (components == NULL)
        {
            printf("Error: Memory not allocated\n");
            exit(1);
        }
    }
    else if (num_components == size_components)
    {
        size_components += 10;
        components = realloc(components, size_components);
        if (components == NULL)
        {
            printf("Error: Memory not allocated\n");
            exit(1);
        }
    }
}

void render_clear_components()
{
    num_components = 0;
    size_components = 0;
}

int render_add_new_component(char *path)
{
    mem_check();

    components[num_components].curr_frame = 0;
    components[num_components].srcRect.w = 32;
    components[num_components].srcRect.h = 32;
    components[num_components].dstRect.w = 32;
    components[num_components].dstRect.h = 32;
    components[num_components].path = calloc(255, sizeof(char));
    if (components[num_components].path == NULL)
    {
        printf("Error: Memory not allocated\n");
        exit(1);
    }
    strcpy(components[num_components].path, path);

    components[num_components].texture = get_texture_by_path(components[num_components].path);

    num_components++;
    return num_components;
}

void render_remove_component_by_index(int index)
{
    render_remove_component(&components[index]);
}

void render_remove_component(RenderComponent **component)
{
    SDL_DestroyTexture((*component)->texture);
    (*component)->texture = NULL;
    free((*component)->path);
    (*component)->path = NULL;
    free(*component);
    *component = NULL;
}

// http://gamedevgeek.com/tutorials/animating-sprites-with-sdl/
int render_tick(Uint32 current)
{
    delta = current - start;

    if (delta > animation_rate)
    {
        for (int i = 0; i < num_components; i++)
        {
            components[i].curr_frame < 2 ? components[i].curr_frame + 1 : 1;
            components[i].curr_frame = components[i].dstRect.x == pos->x ? 0 : components[i].curr_frame;
            components[i].curr_frame = pos->y == 100 ? components[i].curr_frame : 3;
            components[i].curr_frame = components[i].action == 3 ? 4 : components[i].curr_frame;
        }

        start = SDL_GetTicks();
    }

    SDL_RenderClear(rndr);

    for (int i = 0; i < num_components; i++)
    {
        components[i].srcRect.x = components[i].curr_frame * 32;
        components[i].srcRect.y = 0;
        components[i].dstRect.x = pos->x;
        components[i].dstRect.y = pos->y;

        SDL_RenderCopy(rndr, components[i].texture, &components[i].srcRect, &components[i].dstRect);
    }

    SDL_RenderPresent(rndr);
}

void render_destroy()
{
    for (int i = 0; i < num_components; i++)
    {
        render_remove_component(&components[i]);
    }

    SDL_DestroyRenderer(rndr);
    rndr = NULL;

    SDL_DestroyWindow(wnd);
    wnd = NULL;
}

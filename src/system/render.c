#include <SDL.h>
#include "../component/render.h"
#include "../component/position.h"
#include "../component/input.h"
#include "../asset.h"
#include "../manager/entity.h"

#define STB_IMAGE_IMPLEMENTATION
#include "../stb_image.h"

static Entity **entities;
static SDL_Renderer *rndr = NULL;
static SDL_Window *wnd = NULL;

static Uint32 prev_t,
    delta,
    animation_rate = 16.66, // 60fps = 16.66 // 30fps = 33.33
    depth,
    rmask,
    gmask,
    bmask,
    amask;

static int req_format = STBI_rgb_alpha;

static int system_mask = 13;

static SDL_Texture *get_texture_by_path(char *path)
{
    static unsigned char *stbiData = NULL;
    SDL_Texture *tex = NULL;
    SDL_Surface *srfc = NULL;
    int pitch,
        width,
        height,
        orig_format;

    if (!asset_does_file_exist(path))
    {
        printf("Error: File does not exist: %s\n", path);
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

void system_render_set_texture(RenderComponent *cmp, char *path)
{
    strcpy(cmp->path, path);

    cmp->texture = get_texture_by_path(path);
}

int system_render_init()
{
    puts("system_render_init");

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
}

void system_render_tick(Uint32 current_t)
{
    delta = current_t - prev_t;

    Entity *entities = manager_entity_get_entities();
    int num_entities = manager_entity_get_num_entities();

    for (int i = 0; i < num_entities; i++)
    {
        if (entities[i].component_mask & system_mask > 0)
        {
            RenderComponent *r_cmp = entities[i].cmp_render;
            PositionComponent *p_cmp = entities[i].cmp_position;
            InputComponent *i_cmp = entities[i].cmp_position;

            r_cmp->curr_frame < 2 ? r_cmp->curr_frame + 1 : 1;
            r_cmp->curr_frame = r_cmp->dst_rect.x == p_cmp->x ? 0 : r_cmp->curr_frame;
            r_cmp->curr_frame = p_cmp->y == 100 ? r_cmp->curr_frame : 3;
            r_cmp->curr_frame = i_cmp->down ? 4 : r_cmp->curr_frame;
        }
    }

    SDL_RenderClear(rndr);

    for (int i = 0; i < num_entities; i++)
    {
        if (entities[i].component_mask & system_mask > 0)
        {
            RenderComponent *r_cmp = entities[i].cmp_render;
            PositionComponent *p_cmp = entities[i].cmp_position;

            r_cmp->src_rect.x = r_cmp->curr_frame * 32;
            r_cmp->src_rect.y = 0;
            r_cmp->dst_rect.x = p_cmp->x;
            r_cmp->dst_rect.y = p_cmp->y;

            SDL_RenderCopy(rndr, r_cmp->texture, &r_cmp->src_rect, &r_cmp->dst_rect);
        }
    }

    SDL_RenderPresent(rndr);

    prev_t = current_t;

    if (delta > animation_rate) {
        SDL_Delay(delta - animation_rate);
    }
}
#include <SDL.h>
#include "player.h"
#include "utils.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

static SDL_Renderer     *rndr   = NULL;
static SDL_Texture      *txtr   = NULL;
static SDL_Window       *wnd    = NULL;
static Position         *pos    = NULL;
static SDL_Rect         srcRect = { .w = 32, .h = 32 }, 
                        dstRect = { .w = 32, .h = 32 };

static unsigned char    *stbiData = NULL;

static int              current_frame 	= 0,
		  				animation_rate 	= 150;
static Uint32           start, 
                        delta;

static int loadImage()
{
    SDL_Surface *srfc = NULL;

    Uint32  	rmask, 
           		gmask, 
            	bmask, 
            	amask;

    int 		depth, 
        		pitch,
        		width, 
        		height, 
        		orig_format, 
        		req_format = STBI_rgb_alpha;

    stbiData = stbi_load("assets/2.png", &width, &height, &orig_format, req_format);

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

    srfc = SDL_CreateRGBSurfaceFrom((void *)stbiData, width, height, depth, pitch, rmask, gmask, bmask, amask);
    txtr = SDL_CreateTextureFromSurface(rndr, srfc);

    SDL_FreeSurface(srfc);

    srfc        = NULL;
    stbiData    = NULL;
}

int render_init(Uint32 start_t, Position *player_pos)
{
    SDL_Surface *scrnSrfc 	= NULL;

    const int 	SCREEN_WIDTH 	= 640,
		  		SCREEN_HEIGHT 	= 480;

    pos = player_pos;

    start = start_t;

    SDL_Init(SDL_INIT_VIDEO);

    wnd         = SDL_CreateWindow("TBGC", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    rndr        = SDL_CreateRenderer(wnd, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    scrnSrfc    = SDL_GetWindowSurface(wnd);

    loadImage();

    return 0;
}

// http://gamedevgeek.com/tutorials/animating-sprites-with-sdl/

int render_tick(Uint32 current)
{
    delta = current - start;

    if (delta > animation_rate)
    {
        current_frame = current_frame < 2 ? current_frame + 1 : 1;
        current_frame = dstRect.x == pos->x ? 0 : current_frame;
        current_frame = pos->y == 100 ? current_frame : 3; 
        start = SDL_GetTicks();
    }

    srcRect.x = current_frame * 32;
    srcRect.y = 0;

    dstRect.x = pos->x;
    dstRect.y = pos->y;

    SDL_RenderClear(rndr);
    SDL_RenderCopy(rndr, txtr, &srcRect, &dstRect);
    SDL_RenderPresent(rndr);
}

void render_destroy()
{
    stbi_image_free(stbiData);
    
    SDL_DestroyTexture(txtr);
    txtr = NULL;

    SDL_DestroyRenderer(rndr);
    rndr = NULL;

    SDL_DestroyWindow(wnd);
    wnd = NULL;
}

#ifndef COMPONENT_RENDER_H_
#define COMPONENT_RENDER_H_

#include <SDL.h>

typedef struct 
{
    char            *path;
    int             id;
    SDL_Rect        src_rect;
    SDL_Rect        dst_rect;
    SDL_Texture     *texture;
    int             num_frames;
    int             curr_frame;

} RenderComponent; 

#endif
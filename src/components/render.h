#ifndef C_RENDER_H_
#define C_RENDER_H_

#include <SDL.h>

typedef struct {
    int x;
    int y;
} Position;

typedef struct {
    int id, framerate, current_frame;
    char resource_path[255];
    
    SDL_Texture *texture;
    SDL_Rect srcRect, dstRect;
    SDL_Renderer *renderer;
    Uint32 frame_time;

    Position position;
} RenderComponent;

void render_comp_loadImage(RenderComponent *component);
void render_comp_destroy(RenderComponent *component);

#endif
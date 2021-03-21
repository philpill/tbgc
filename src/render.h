#ifndef RENDER_H_
#define RENDER_H_

#include <SDL.h>
#include "player.h"

typedef struct renderComponent {

    char            *path;
    int             num_frames;
    int             curr_frame;
    EntityType      entityType;
    SDL_Texture     *texture;
    int             action;
    SDL_Rect        srcRect;
    SDL_Rect        dstRect;

} RenderComponent;

int render_init(Uint32 start_t, Position *player_pos, PlayerAction *player_action);
int render_tick(Uint32 current_t);
void render_destroy();
int render_add_new_component(char *path);
RenderComponent **render_get_components();
RenderComponent *render_get_component_by_path(char* path);
RenderComponent *render_get_component_by_index(int index);
void render_remove_component(RenderComponent **component);
void render_remove_component_by_index(int index);

#endif
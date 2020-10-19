#ifndef S_RENDER_H_
#define S_RENDER_H_

#include "../components/render.h";

void s_render_init();
void s_render_add_component(RenderComponent *component);
void s_render_tick();
void s_render_destroy();

#endif
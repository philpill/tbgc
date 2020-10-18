#ifndef S_RENDER_H_
#define S_RENDER_H_

void render_system_init();
void render_system_add_component(RenderComponent *component);
void render_system_tick();
void render_system_destroy();

#endif
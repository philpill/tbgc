#ifndef S_EVENT_H_
#define S_EVENT_H_

#include "../components/render.h";

int s_event_init();
void s_event_add_component(RenderComponent *component);
int s_event_tick();

#endif
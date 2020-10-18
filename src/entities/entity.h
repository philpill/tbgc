#ifndef E_ENTITY_H_
#define E_ENTITY_H_

#include "components/render.h"

typedef enum {
    Player
} EntityType;

typedef struct {
    int id;
    EntityType entity_type;
    RenderComponent render_component;
} Entity;

#endif
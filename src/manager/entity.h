#ifndef MANAGER_ENTITY_H_
#define MANAGER_ENTITY_H_

#include "../component/physics.h"
#include "../component/render.h"
#include "../component/movement.h"
#include "../component/position.h"
#include "../component/input.h"

typedef struct
{
    int id;
    int component_mask;
    PhysicsComponent *cmp_physics;
    MovementComponent *cmp_movement;
    PositionComponent *cmp_position;
    RenderComponent *cmp_render;
    InputComponent *cmp_input;

} Entity;

void manager_entity_init();
int manager_entity_get_num_entities();
Entity *manager_entity_get_entities();

int manager_entity_insert_entity(Entity *entity);
int manager_entity_remove_entity(Entity *entity);

void manager_entity_add_player_entity();

#endif
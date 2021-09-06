#include <SDL.h>
#include <string.h>
#include "../utils.h"
#include "./entity.h"
#include "../constants.h"
#include "../system/physics.h"

#include "../component/input.h"
#include "../component/movement.h"
#include "../component/position.h"
#include "../component/render.h"
#include "../component/physics.h"

Entity *entities;
static int num_entities = 0;
static int size_entities = 1;

Entity *manager_entity_get_entities()
{
    return entities;
}

int manager_entity_get_num_entities()
{
    return num_entities;
}

int manager_entity_insert_entity(Entity *entity)
{
    if (num_entities == size_entities)
    {
        size_entities = size_entities == 0 ? 1 : size_entities * 2;
        entities = utils_realloc(entities, size_entities * sizeof(Entity));
    }

    // set properties
    entities[num_entities].id = num_entities;
    entities[num_entities].component_mask = 15;
    entities[num_entities].cmp_input = entity->cmp_input;
    entities[num_entities].cmp_movement = entity->cmp_movement;
    entities[num_entities].cmp_position = entity->cmp_position;
    entities[num_entities].cmp_render = entity->cmp_render;
    entities[num_entities].cmp_physics = entity->cmp_physics;

    // create components

    // update number of entities
    num_entities++;

    return num_entities;
}

int manager_entity_remove_entity(Entity *entity)
{
    if (num_entities == 0) return 0;

    // delete components

    return num_entities;
}

void manager_entity_init()
{
    num_entities = 0;
    size_entities = 0;

    entities = utils_calloc(num_entities, sizeof(Entity));
}

void manager_entity_add_player_entity()
{
    Entity *entity =        utils_malloc(sizeof(Entity));

    entity->cmp_input =     utils_malloc(sizeof(InputComponent));
    entity->cmp_movement =  utils_malloc(sizeof(MovementComponent));
    entity->cmp_position =  utils_malloc(sizeof(PositionComponent));
    entity->cmp_render =    utils_malloc(sizeof(RenderComponent));
    entity->cmp_physics =   utils_malloc(sizeof(PhysicsComponent));

    entity->cmp_movement->acc_max_x = ACC_X_MAX;
    entity->cmp_movement->acc_min_x = ACC_X_MIN;

    entity->cmp_movement->acc_max_y = ACC_Y_MAX;
    entity->cmp_movement->acc_min_y = ACC_Y_MIN;

    entity->cmp_movement->vel_max_x = 200;
    entity->cmp_movement->vel_min_x = -200;

    entity->cmp_movement->vel_max_y = 100;
    entity->cmp_movement->vel_min_y = -100;

    entity->cmp_render->path = utils_malloc(255 * sizeof(char));
    entity->cmp_render->src_rect.h = 32;
    entity->cmp_render->src_rect.w = 32;
    entity->cmp_render->dst_rect.h = 32;
    entity->cmp_render->dst_rect.w = 32;

    entity->cmp_position->x = 10;
    entity->cmp_position->y = 100;

    system_render_set_texture(entity->cmp_render, "assets/2.png");

    manager_entity_insert_entity(entity);
}
#include <SDL.h>
#include "../component/physics.h"
#include "../utils.h"
#include "../manager/entity.h"

static int system_mask = 1;

int system_physics_init()
{
    puts("system_physics_init");
}

void system_physics_tick(Uint32 current)
{
    Entity *entities = manager_entity_get_entities();
    int num_entities = manager_entity_get_num_entities();

    // loop over entities
    for (int i = 0; i < num_entities; i++)
    {
        // get entities with relevant components
        if (entities[i].component_mask & system_mask > 0)
        {
            PhysicsComponent *p_cmp = entities[i].cmp_physics; 

            // physics operations
            // if (p_cmp->acc_x != 0)
            // {
            //     utils_clamp(&p_cmp->acc_x, p_cmp->acc_min_x, p_cmp->acc_max_x);
            //     p_cmp->acc_x = p_cmp->acc_x < 0.1 && p_cmp->acc_x > -0.1 ? 0 : p_cmp->acc_x;
            //     p_cmp->acc_x = p_cmp->acc_x * 0.75;
            //     p_cmp->pos.x = (int)(p_cmp->pos.x + p_cmp->acc_x);
            // }

            // utils_clamp(&p_cmp->acc_y, p_cmp->acc_min_y, p_cmp->acc_max_y);
            // p_cmp->acc_y++;
            // p_cmp->acc_y = p_cmp->acc_y > 10 ? 10 : p_cmp->acc_y;
            // p_cmp->pos.y = p_cmp->pos.y + p_cmp->acc_y;
            // p_cmp->pos.y = p_cmp->pos.y > 100 ? 100 : p_cmp->pos.y;
        }
    }
}
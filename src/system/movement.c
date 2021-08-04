#include <SDL.h>
#include <stdlib.h>
#include "../manager/entity.h"
#include "../component/input.h"
#include "../component/physics.h"
#include "../utils.h"
#include "../constants.h"

static int system_mask = 10;
static Uint32 prev_t;
static SDL_Event e;

int system_movement_init()
{
    puts("system_movement_init");
}

void system_movement_tick(Uint32 current_t)
{
    double diff_t = (double)(current_t - prev_t);
    double diff_t_seconds = diff_t/1000.0;

    Entity *entities = manager_entity_get_entities();
    int num_entities = manager_entity_get_num_entities();

    // loop over entities
    for (int i = 0; i < num_entities; i++)
    {
        // get entities with relevant components
        if (entities[i].component_mask & system_mask > 0)
        {
            InputComponent *i_cmp = entities[i].cmp_input;
            MovementComponent *m_cmp = entities[i].cmp_movement;
            PositionComponent *p_cmp = entities[i].cmp_position;

            int acc_x = 0;

            if (i_cmp->left) 
            {
                acc_x = -3000;
            }

            if (i_cmp->right) 
            {
                acc_x = 3000;
            }

            m_cmp->vel_x = acc_x != 0 ? m_cmp->vel_x + (acc_x * diff_t_seconds): 0;

            utils_clamp(&m_cmp->vel_x, m_cmp->vel_min_x, m_cmp->vel_max_x);

            // position
            p_cmp->x = p_cmp->x + m_cmp->vel_x * diff_t_seconds;

            // limit to screen
            utils_clamp(&p_cmp->x, 0, SCREEN_WIDTH - 32);

            // friction
            m_cmp->vel_x = m_cmp->vel_x * pow(0.01, diff_t_seconds);

            // utils_clamp(&m_cmp->acc_y, m_cmp->acc_min_y, m_cmp->acc_max_y);
            // m_cmp->acc_y++;
            // m_cmp->acc_y = m_cmp->acc_y > 10 ? 10 : m_cmp->acc_y;
            // p_cmp->y = p_cmp->y + m_cmp->acc_y;
            // p_cmp->y = p_cmp->y > 100 ? 100 : p_cmp->y;
        
        }
    }

    prev_t = current_t;
}

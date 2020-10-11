#include "player.h"
#include "utils.h"

static Player player;

int player_init(Position **pos)
{
    player = (Player) {
        .acceleration_x = 0, 
        .acceleration_y = 0, 
        .acceleration_min_x = -10,
        .acceleration_max_x = 10,
        .acceleration_min_y = -10,
        .acceleration_max_y = 10,
        .position = (Position) { 
            .x = 0, 
            .y = 100 
        }
    };

    *pos = &player.position;
}

int player_tick()
{
    if (player.acceleration_x != 0) 
    {
        utils_clamp(&player.acceleration_x, player.acceleration_min_x, player.acceleration_max_x);

        player.acceleration_x = player.acceleration_x < 0.1 && player.acceleration_x > -0.1 ? 0 : player.acceleration_x;

        player.acceleration_x = player.acceleration_x * 0.75;

        player.position.x = (int)(player.position.x + player.acceleration_x);
    }
}

void player_accelerate_x(int delta) { player.acceleration_x += delta; }
void player_accelerate_y(double delta) { player.acceleration_y += delta; }
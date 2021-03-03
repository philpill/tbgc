#include <SDL.h>
#include "player.h"
#include "utils.h"

static Player player;

int player_init(Position **pos, PlayerAction **action)
{
    player = (Player){
        .action = 0,
        .acc_x = 0,
        .acc_y = 10,
        .acc_min_x = -10,
        .acc_max_x = 10,
        .acc_min_y = -100,
        .acc_max_y = 10,
        .position = (Position){
            .x = 0,
            .y = 100}};

    *pos    = &player.position;
    *action = &player.action;
}

int player_tick(Uint32 current)
{
    player_x_tick();
    player_y_tick();
}

int player_x_tick()
{
    if (player.acc_x != 0)
    {
        utils_clamp(&player.acc_x, player.acc_min_x, player.acc_max_x);

        player.acc_x = player.acc_x < 0.1 && player.acc_x > -0.1 ? 0 : player.acc_x;

        player.acc_x = player.acc_x * 0.75;

        player.position.x = (int)(player.position.x + player.acc_x);
    }
}

int player_y_tick()
{
    utils_clamp(&player.acc_y, player.acc_min_y, player.acc_max_y);

    player.acc_y++;

    player.acc_y = player.acc_y > 10 ? 10 : player.acc_y;

    player.position.y = player.position.y + player.acc_y;

    player.position.y = player.position.y > 100 ? 100 : player.position.y;
}

void player_acc_x(int delta) { player.acc_x += delta; }
void player_acc_y(int delta)
{
    player.acc_y += delta;
}

void player_default()
{
    player.action = 0;
}

void player_jump()
{
    if (player.position.y == 100)
    {
        player_acc_y(-23);
    }
}

void player_crouch()
{
    if (player.position.y == 100)
    {
        player.action = 3;
    }
}

void player_forward()
{
    player_acc_x(7);
}

void player_backward()
{
    player_acc_x(-7);
}
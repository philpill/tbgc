#ifndef PLAYER_H_
#define PLAYER_H_

#include "./components/render.h";

typedef struct {
    int acceleration_x;
    int acceleration_y;
    int acceleration_max_x;
    int acceleration_min_x;
    int acceleration_max_y;
    int acceleration_min_y;
    Position position;
} Player;

int player_init(Position **pos);
int player_tick();

#endif
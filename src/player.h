#ifndef PLAYER_H_
#define PLAYER_H_

typedef struct {
    int x;
    int y;
} Position;

typedef struct {
    int acc_x;
    int acc_y;
    int acc_max_x;
    int acc_min_x;
    int acc_max_y;
    int acc_min_y;
    Position position;
} Player;

int player_init(Position **pos);
int player_tick();

#endif

#ifndef PLAYER_H_
#define PLAYER_H_

typedef struct {
    int x;
    int y;
} Position;

typedef enum {
    DEFAULT,
    MOVE,
    JUMP,
    CROUCH
} PlayerAction;

typedef enum {
    UNDEFINED,
    PLAYER,
    BLOCK
} EntityType;

typedef struct {
    int acc_x;
    int acc_y;
    int acc_max_x;
    int acc_min_x;
    int acc_max_y;
    int acc_min_y;
    Position position;
    PlayerAction action;

} Player;


int player_init(Position **pos, PlayerAction **action);
int player_tick(Uint32 current);

void player_acc_x(int delta);
void player_acc_y(int delta);

void player_default();
void player_jump();
void player_crouch();
void player_forward();
void player_backward();
#endif

#ifndef PLAYER_H_
#define PLAYER_H_

typedef struct {
    int x;
    int y;
} position;

int player_init();
int player_handle();

#endif
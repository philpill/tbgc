#include "player.h"

static int acceleration_x = 0;
static int acceleration_y = 0;

int player_init()
{

}

int player_handle(position *pos)
{
    printf("alpha1: %d\n", pos->x);
    printf("alpha2: %d\n", acceleration_x);

    pos->x = pos->x + acceleration_x;
 

    printf("alpha3: %d\n", pos->x);
    printf("alpha4: %d\n", acceleration_x);


    acceleration_x *= 0.75;
    acceleration_x = acceleration_x < 0.01 ? 0 : acceleration_x;
}

void player_accelerate_x(int delta) 
{ 
    printf("bravo1: %d\n", delta);
    printf("bravo2: %d\n", acceleration_x);
    acceleration_x += delta; 
    printf("bravo3: %d\n", acceleration_x);
}

void player_accelerate_y(double delta) { acceleration_y += delta; }
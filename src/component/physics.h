#ifndef COMPONENT_PHYSICS_H_
#define COMPONENT_PHYSICS_H_

typedef struct {
    int x;
    int y;
} Position;

typedef struct
{
    int id;
    int acc_x;
    int acc_y;
    int acc_max_x;
    int acc_min_x;
    int acc_max_y;
    int acc_min_y;
    Position pos;

} PhysicsComponent;

#endif
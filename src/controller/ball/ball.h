#ifndef BALL
#define BALL

#include "stdio.h"
#include "stdlib.h"
#include "../video/graphics.h"
#include "../../model/model.h"
#include "../brick/brick.h"

typedef struct {
    uint16_t radius;
    uint16_t x;
    uint16_t y;
    int16_t vx;
    int16_t vy;
    uint8_t power;
    uint16_t speed;
}Ball;
void change_ball_pos(Ball* ball);

void collision_board(Ball* ball);

void collision_brick(Ball* ball, Brick* brick);

#endif

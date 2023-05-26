#ifndef BALL
#define BALL

#include "stdio.h"
#include "stdlib.h"
#include "../video/graphics.h"
#include "../../model/model.h"
#include "brick.h"
#include "paddle.h"

void change_ball_pos(Ball* ball);

void collision_board(Ball* ball);

void collision_brick(Ball* ball, Brick* brick);

void collision_paddle(Ball* ball, Paddle* paddle);

int16_t clamp(int16_t value, int16_t min, int16_t max);

#endif

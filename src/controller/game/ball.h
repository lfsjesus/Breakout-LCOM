#ifndef BALL
#define BALL

#include "stdio.h"
#include "stdlib.h"
#include "../video/graphics.h"
#include "../../model/model.h"
#include "brick.h"

void change_ball_pos(Ball* ball);

void collision_board(Ball* ball);

void collision_brick(Ball* ball, Brick* brick);

#endif

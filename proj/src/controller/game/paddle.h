#ifndef PADDLE_H
#define PADDLE_H

#include "stdlib.h"
#include "stdio.h"
#include "../../model/model.h"
#include "../keyboard_mouse/keyboard.h"
#include "../keyboard_mouse/mouse.h"
#include "../video/graphics.h"

void move_paddle(Paddle* paddle);

void mouse_move_paddle(Paddle* paddle);

void move_paddle_and_ball(Paddle* paddle, Ball* ball);

void increase_points();

void reset_points();

int getPoints();

int getLives();

void decreaseLives();

void increaseLives();

void reset_paddle(Paddle* paddle);

void reset_lives();

#endif

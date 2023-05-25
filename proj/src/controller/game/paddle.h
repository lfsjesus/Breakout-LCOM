#ifndef PADDLE_H
#define PADDLE_H

#include "stdlib.h"
#include "stdio.h"
#include "../../model/model.h"
#include "../keyboard_mouse/keyboard.h"
#include "../keyboard_mouse/mouse.h"
#include "../video/graphics.h"

void movePaddle(Paddle* paddle);

void increasePoints();

int getPoints();

int getLives();

#endif

#ifndef POWERUP_H
#define POWERUP_H

#include "../../model/model.h"
#include "paddle.h"
#include "ball.h"

void drop_random_powerup();

void disable_powerup(PowerUp *powerup);

void activate_powerup(PowerUp *powerup);

void move_active_powerups();

void check_powerup_collision(Paddle *paddle);

bool extra_ball_active();

#endif

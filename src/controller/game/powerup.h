#ifndef POWERUP_H
#define POWERUP_H

#include "../../model/model.h"
#include "paddle.h"
#include "ball.h"

/**
 * @brief Drops a random powerup from a random position
 */
void drop_random_powerup();
/**
 * @brief Sets the powerup active to false 
 * @param powerup pointer to the powerup
 */
void disable_powerup(PowerUp *powerup);
/**
 * @brief Activates the power up according to its type
 * @param powerup pointer to the powerup
 */
void activate_powerup(PowerUp *powerup);
/**
 * @brief Moves all active powerup down the screen
 */
void move_active_powerups();
/**
 * @brief Handles active power ups collision with the paddle
 * @param paddle pointer to the paddle
 */
void check_powerup_collision(Paddle *paddle);
/**
 * @brief Checks if extra ball is active
 * @return true if extra ball is active
 * @return false if extra ball is not active
 */
bool extra_ball_active();

void reset_powerups();

#endif

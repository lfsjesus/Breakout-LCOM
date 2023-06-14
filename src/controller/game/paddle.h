#ifndef PADDLE_H
#define PADDLE_H

#include "stdlib.h"
#include "stdio.h"
#include "../../model/model.h"
#include "../keyboard_mouse/keyboard.h"
#include "../keyboard_mouse/mouse.h"
#include "../video/graphics.h"

/**
 * @brief Checks if paddle should be moved with keyboard or mouse
 * and handles it accordingly
 * @param paddle pointer to the paddle
 */
void move_paddle(Paddle* paddle);
/**
 * @brief Handles paddle movement with mouse
 * @param paddle pointer to the paddle
 */
void mouse_move_paddle(Paddle* paddle);
/**
 * @brief Moves paddle and ball according to the paddle
 * @param paddle pointer to the paddle
 * @param ball pointer to the ball
 */
void move_paddle_and_ball(Paddle* paddle, Ball* ball);
// FALTA AQUI O KEYBOARD MOVE PADDLE
/**
 * @brief Increases the player points by 1
 */
void increase_points();
/**
 * @brief Sets the player points to 0
 */
void reset_points();
/**
 * @brief Gets the player's points
 * @return int player's points
 */
int getPoints();
/**
 * @brief Gets the player's number of lives
 * @return int player's number of lives
 */
int getLives();
/**
 * @brief Decreases the player's number of lives by 1
 */
void decreaseLives();
/**
 * @brief Increases the player's number of lives by 1
 */
void increaseLives();
/**
 * @brief Resets the paddle to the position (350, 550)
 * @param paddle pointer to the paddle
 */
void reset_paddle(Paddle* paddle);
/**
 * @brief Sets the player's number of lives to 3
 */
void reset_lives();

#endif

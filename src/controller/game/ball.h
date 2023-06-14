#ifndef BALL
#define BALL

#include "stdio.h"
#include "stdlib.h"
#include "../video/graphics.h"
#include "../../model/model.h"
#include "brick.h"
#include "paddle.h"
#include "powerup.h"

/**
 * @brief Changes the position of the ball
 * @param ball pointer to the ball
 */
void change_ball_pos(Ball* ball);
/**
 * @brief Handles ball collisions with edges of the screen
 * @param ball pointer to the ball
 */
void collision_board(Ball* ball);
/**
 * @brief Handles ball-brick collisions
 * @param ball pointer to the ball
 * @param brick pointer to the brick
 */
void collision_brick(Ball* ball, Brick* brick);
/**
 * @brief Handles ball-extraBall collisions
 * @param ball pointer to the ball
 * @param extraBall pointer to the extra ball
 */
void collision_extra_ball(Ball* ball, Ball* extraBall);
/**
 * @brief Handles ball-paddle collisions
 * @param ball pointer to the ball
 * @param paddle pointer to the paddle
 */
void collision_paddle(Ball* ball, Paddle* paddle);
/**
 * @brief Checks if ball is out of the screen
 * @param ball pointer to the ball
 * @return true if ball is out of the screen
 * @return false if ball is inside the screen
 */
bool check_ball_out(Ball* ball, Paddle* paddle);
/**
 * @brief Resets the ball
 * @param ball pointer to the ball
 */
void reset_ball(Ball* ball);
/**
 * @brief Adds a new ball to the game
 * @param mainBall pointer to the main ball
 * @param newBall pointer to the new ball
 */
void add_ball(Ball* mainBall, Ball* newBall);
/**
 * @brief Disables a ball 
 * @param ball pointer to the ball
 */
void disable_extra_ball(Ball* ball);

#endif

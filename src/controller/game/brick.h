#ifndef BRICK
#define BRICK

#include "stdlib.h"
#include "stdio.h"
#include "../../model/model.h"

/**
 * @brief Decreases the hp of the brick by 1.
 * If the hp is 0 after decreasing, removes brick and updates brick counter.
 * @param brick pointer to the brick
 */
void decrease_hp(Brick* brick);
/**
 * @brief Reduces 4hp from red bricks.
 */
void destroy_red_bricks();

#endif

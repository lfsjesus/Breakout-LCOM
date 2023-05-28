#ifndef _LCOM_MODEL_H_
#define _LCOM_MODEL_H_

#include <minix/sysutil.h>
#include <lcom/lcf.h>
#include "xpm/mouse.xpm"
#include "xpm/menu_background.xpm"
#include "xpm/controller_mouse.xpm"
#include "xpm/controller_keyboard.xpm"
#include "xpm/ball_option1.xpm"
#include "xpm/ball_option2.xpm"
#include "xpm/paddle_option1.xpm"
#include "xpm/paddle_option2.xpm"
#include "xpm/paddle.xpm"
#include "xpm/paddle2.xpm"
#include "xpm/heart.xpm"
#include "xpm/ball.xpm"
#include "xpm/ball2.xpm"
#include "xpm/extra_ball.xpm"
#include "../model/sprite.h"
#include "../model/maps/maps.h"
#include "xpm/bricks.h"
#include "xpm/ball_power.xpm"
#include "xpm/block_power.xpm"
#include "xpm/life_power.xpm"
#include "xpm/font/font.h"

/**
 * @brief Set up all sprite object
 */
void setup_sprites();
/**
 * @brief Destroys all the sprite objects
 * Important to use this before ending the game loop
 */
void destroy_sprites();
/**
 * @brief Set up all the bricks for the game
 */
void setup_bricks();
/**
 * @brief Set up all the powerups for the game
 */
void setup_powerups();
/**
 * @brief Set up the ball object for the game
 * @param n current setting
 */
void setup_ball(uint8_t n);
/**
 * @brief Set up the paddle object for the game
 * @param n current setting
 */
void setup_paddle(uint8_t n);

/**
 * @brief struct used for brick objects
 */
typedef struct {
    Sprite* sprite;     /**< Pointer to the sprite object representing the brick. */
    uint16_t x;         /**< The x-coordinate of the brick. */
    uint16_t y;         /**< The y-coordinate of the brick. */
    uint8_t hp;         /**< The health points (HP) of the brick. */
} Brick;

/**
 * @brief Struct used for ball objects
 */
typedef struct {
    Sprite* sprite;     /**< Pointer to the sprite object representing the ball. */
    uint16_t radius;    /**< The radius of the ball. */
    uint16_t x;         /**< The x-coordinate of the ball. */
    uint16_t y;         /**< The y-coordinate of the ball. */
    int16_t vx;         /**< The x-velocity of the ball. */
    int16_t vy;         /**< The y-velocity of the ball. */
    uint8_t power;
    uint16_t speed;
} Ball;

/**
 * @brief Struct used for paddle objects
 */
typedef struct {
    Sprite* sprite;     /**< Pointer to the sprite object representing the paddle. */
    uint16_t x;         /**< The x-coordinate of the paddle. */
    uint16_t y;         /**< The y-coordinate of the paddle. */
} Paddle;

/**
 * @brief Struct used for powerup objects
 */
typedef struct {
    Sprite* sprite;     /**< Pointer to the sprite object representing the powerup. */
    uint16_t x;         /**< The x-coordinate of the powerup. */
    uint16_t y;         /**< The y-coordinate of the powerup. */
    uint8_t type;       /**< The type of the powerup. */
    bool active;        /**< If the powerup is active or not. */
} PowerUp;

typedef enum {
    MOUSE,
    KEYBOARD,
} ControlDevice;

/**
 * @brief Variable that holds the current number of bricks in the game
 */
static int brick_counter = 0;

/**
 * @brief Gets the current number of bricks in the game
 * @return int - current number of bricks in the game
 */
int getBrickCounter();

/**
 * @brief decrements the brick_counter variable by 1
 */
void decrementBrickCounter();

#endif

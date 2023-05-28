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
#include "xpm/leaderboard.xpm"
#include "xpm/extra_ball.xpm"
#include "../model/sprite.h"
#include "../model/maps/maps.h"
#include "xpm/bricks.h"
#include "xpm/ball_power.xpm"
#include "xpm/block_power.xpm"
#include "xpm/life_power.xpm"
#include "xpm/font/font.h"

void setup_sprites();
void destroy_sprites();
void setup_bricks();
void setup_powerups();
void setup_ball(uint8_t n);
void setup_paddle(uint8_t n);

typedef struct {
    Sprite* sprite; 
    uint16_t x;
    uint16_t y;
    uint8_t hp;
} Brick;

typedef struct {
    Sprite* sprite;
    uint16_t radius;
    uint16_t x;
    uint16_t y;
    int16_t vx;
    int16_t vy;
    uint8_t power;
    uint16_t speed;
} Ball;

typedef struct {
    Sprite* sprite;
    uint16_t x;
    uint16_t y;
} Paddle;

typedef struct {
    Sprite* sprite;
    uint16_t x;
    uint16_t y;
    uint8_t type;
    bool active;
} PowerUp;

typedef enum {
    MOUSE,
    KEYBOARD,
} ControlDevice;

static int brick_counter = 0;

int getBrickCounter();

void decrementBrickCounter();



#endif

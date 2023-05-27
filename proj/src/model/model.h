#ifndef _LCOM_MODEL_H_
#define _LCOM_MODEL_H_

#include <minix/sysutil.h>
#include <lcom/lcf.h>
#include "xpm/mouse.xpm"
#include "xpm/menu_background.xpm"
#include "xpm/singleplayer_button.xpm"
#include "xpm/multiplayer_button.xpm"
#include "xpm/leaderboard_button.xpm"
#include "xpm/settings_button.xpm"
#include "xpm/paddle.xpm"
#include "xpm/heart.xpm"
#include "xpm/ball.xpm"
#include "../model/sprite.h"
#include "../model/maps/maps.h"
#include "xpm/bricks.h"
#include "xpm/font/font.h"

void setup_sprites();
void destroy_sprites();
void setup_bricks();

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

typedef enum {
    MOUSE,
    KEYBOARD,
} ControlDevice;

static int brick_counter = 0;

int getBrickCounter();

void decrementBrickCounter();

#endif

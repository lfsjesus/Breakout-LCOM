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
#include "../model/sprite.h"
#include "../model/maps/map1.c"

void setup_sprites();
void destroy_sprites();
void setup_bricks();

typedef struct {
    uint16_t x;
    uint16_t y;
    uint16_t width;
    uint16_t height;
    uint8_t hp;
    uint8_t color;
} Brick;

typedef struct {
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


#endif

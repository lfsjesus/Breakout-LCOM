#ifndef _LCOM_MODEL_H_
#define _LCOM_MODEL_H_

#include <minix/sysutil.h>
#include <lcom/lcf.h>
#include "../controller/keyboard_mouse/keyboard.h"
#include "../controller/keyboard_mouse/mouse.h"
#include "../controller/video/graphics.h"
#include "xpm/mouse.xpm"
#include "xpm/menu_background.xpm"
#include "xpm/singleplayer_button.xpm"
#include "xpm/multiplayer_button.xpm"
#include "xpm/leaderboard_button.xpm"
#include "xpm/settings_button.xpm"
#include "../view/view.h"
#include "../model/sprite.h"

void setup_sprites();
void destroy_sprites();
void update_keyboard_state();
void update_mouse_state();
void update_timer_state();


typedef enum {
    RUNNING,
    EXIT,
} SystemState;

typedef enum {
    START,
    GAME,
    SCORE,
    SETTINGS,
    END
} GameState;

typedef struct {
    uint16_t radius;
    uint16_t x;
    uint16_t y;
    int16_t vx;
    int16_t vy;
    uint8_t power;
    uint16_t speed;
}Ball;

typedef struct {
    uint16_t width;
    uint16_t height;
    uint16_t x;
    uint16_t y;
    uint8_t hp;
}Brick;

void update_ball_pos(Ball* ball);


#endif

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
#include "../model/maps/map1.c"
#include "../controller/ball/ball.h"
#include "../controller/brick/brick.h"


void setup_sprites();
void destroy_sprites();
void setup_bricks();

void update_keyboard_state();
void update_mouse_state();
void update_timer_state();

void refresh_buttons_state();


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

#endif

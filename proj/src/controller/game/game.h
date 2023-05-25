#ifndef GAME_CONTROLLER_H
#define GAME_CONTROLLER_H

#include <minix/sysutil.h>
#include <lcom/lcf.h>
#include "../../controller/keyboard_mouse/mouse.h"
#include "../../controller/video/graphics.h"
#include "../../controller/serialPort/serialport.h"
#include "paddle.h"
#include "ball.h"
#include "brick.h"
#include "../../view/view.h"

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

void update_keyboard_state();
void update_mouse_state();
void update_timer_state();
void update_sp_state();
void refresh_buttons_state();

#endif

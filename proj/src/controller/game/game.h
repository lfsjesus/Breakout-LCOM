#ifndef GAME_CONTROLLER_H
#define GAME_CONTROLLER_H

#include <minix/sysutil.h>
#include <lcom/lcf.h>
#include "../../controller/keyboard_mouse/mouse.h"
#include "../../controller/video/graphics.h"
#include "../../controller/rtc/rtc.h"
#include "../../view/view.h"
#include "leaderboard.h"
#include "paddle.h"
#include "ball.h"
#include "brick.h"
#include "powerup.h"

typedef enum {
    RUNNING,
    EXIT,
} SystemState;

typedef enum {
    START,
    INIT,
    SINGLEPLAYER,
    LEADERBOARD,
    SETTINGS,
    END
} AppState;

void update_keyboard_state();
void update_mouse_state();
void update_timer_state();
void update_rtc_state();
void refresh_buttons_state();
void reset_game();
void update_settings_state();
void settings_keyboard_state();
void settings_mouse_state();
void settings_change_control_device();
void singleplayer_handler();
uint8_t get_current_setting();
ControlDevice get_control_device();

#endif

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

/**
 * @brief Enum with the system states
 */
typedef enum {
    RUNNING,
    EXIT,
} SystemState;

/**
 * @brief Enum with all the game states
 */
typedef enum {
    START,
    INIT,
    SINGLEPLAYER,
    LEADERBOARD,
    SETTINGS,
    END
} AppState;

/**
 * @brief Updates states according to keyboard usage
 */
void update_keyboard_state();
/**
 * @brief Updates states according to mouse usage
 */
void update_mouse_state();
/**
 * @brief Updates states according to timer
 */
void update_timer_state();
<<<<<<< HEAD
void update_rtc_state();
=======
/**
 * @brief Updates states according to mouse clicks
 */
>>>>>>> documentation
void refresh_buttons_state();
/**
 * @brief Resets the game (ball, paddle, bricks, lives and points)
 */
void reset_game();
/**
 * @brief Sets up the game according to the settings
 */
void update_settings_state();
/**
 * @brief Sets the settings according to key pressed in the keyboard
 */
void settings_keyboard_state();
/**
 * @brief Sets the settings accoring to mouse usage
 */
void settings_mouse_state();
/**
 * @brief Sets the control device (mouse or keyboard) according to settings
 */
void settings_change_control_device();
/**
 * @brief Handles the single player game mode
 */
void singleplayer_handler();
/**
 * @brief Gets the current setting
 * @return uint8_t current setting
 */
uint8_t get_current_setting();
/**
 * @brief Gets the current control device
 * @return ControlDevice current control device
 */
ControlDevice get_control_device();

#endif

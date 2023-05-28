#include "game.h"
#include <lcom/lcf.h>

extern uint8_t scancode;
extern uint8_t packet_counter;
extern uint32_t counter; // Timer counter

SystemState systemState = RUNNING;
AppState gameState = START;
ControlDevice controlDevice = MOUSE;

extern vbe_mode_info_t mode_info;
extern MouseInfo mouse_info;
extern rtc_time_info rtc_time;

extern Paddle mainPaddle;
extern Ball mainBall;
extern Ball extraBall;

uint8_t current_setting = 0; // Value between 0 and 5 (settings' screens)

char** levels[3] = {map1, map2, map3};
static int current_level = 0;

uint8_t get_current_setting() {
    return current_setting;
}

ControlDevice get_control_device() {
    return controlDevice;
}

void update_keyboard_state() {
    (kbc_ih)();
    switch (gameState) {
    case START:
        switch (scancode) {
            case ESC_BK_CODE:
                systemState = EXIT;
                break;
            case ONE_BK_CODE:
                gameState = INIT;
                break;
            case TWO_BK_CODE:
                break;
            case THREE_BK_CODE:
                gameState = LEADERBOARD;
                leaderboard_fill();
                break;
            case FOUR_BK_CODE:
                gameState = SETTINGS;
                break;
        }
        break;
    case SETTINGS: 
        if (controlDevice == KEYBOARD) {
            settings_keyboard_state();
            update_settings_state();
        }
        if (scancode == ESC_BK_CODE) gameState = START;
        break;
    default:
        switch (scancode){
            case ESC_BK_CODE:
                reset_game();
                gameState = START;
            default:
                break;
            }
        break;
    
}
}
void update_mouse_state() {
    mouse_ih();
    mouse_sync();
    if (packet_counter == 3) {
        sync_mouse_info();
    }
    switch (gameState) {
        case START: 
            refresh_buttons_state();
            break;
        case INIT:
            move_paddle_and_ball(&mainPaddle, &mainBall);
        case SINGLEPLAYER:
            collision_paddle(&mainBall, &mainPaddle);
            move_paddle(&mainPaddle);
            collision_paddle(&mainBall, &mainPaddle);
            break;
        case SETTINGS:
            if (controlDevice == MOUSE) {
                settings_mouse_state();
                update_settings_state();
            }
            break;
        default:
            break;
    }
}

void update_timer_state() {
    switch (gameState) {
        case START:
            reset_ball(&mainBall);
            break;
        case INIT:
            if (controlDevice == KEYBOARD) {
                move_paddle_and_ball(&mainPaddle, &mainBall);
                if (scancode == SPACE_BK_CODE) {
                    gameState = SINGLEPLAYER;
                }
            }
            else {
                if (mouse_info.right_click) {
                    gameState = SINGLEPLAYER;
                }
            }

            break;
        case SINGLEPLAYER:
            timer_int_handler();
            singleplayer_handler();
            update_rtc_state(); 
            break;
        default:
            break;
    }
    vg_set_start();
    clear_screen();
    draw_new_frame();
}

void update_rtc_state() {
    rtc_update();
}

void refresh_buttons_state() {
    if (mouse_info.left_click) {
        if (mouse_info.x >= 100 && mouse_info.x <= 380 && mouse_info.y >= 250 && mouse_info.y <= 350) {
            gameState = INIT;
        }
        else if (mouse_info.x >= 420 && mouse_info.x <= 700 && mouse_info.y >= 250 && mouse_info.y <= 350) {
            gameState = SINGLEPLAYER;
        }
        else if (mouse_info.x >= 100 && mouse_info.x <= 380 && mouse_info.y >= 350 && mouse_info.y <= 450) {
            gameState = LEADERBOARD;
            leaderboard_fill();
        }
        else if (mouse_info.x >= 420 && mouse_info.x <= 700 && mouse_info.y >= 350 && mouse_info.y <= 450) {
            gameState = SETTINGS;
        }
    }
}

void update_settings_state() {
    setup_ball(current_setting);
    setup_paddle(current_setting);
    settings_change_control_device();
}

void settings_keyboard_state() {
    switch (scancode) {
        case ESC_BK_CODE:
            gameState = START;
            break;
        case ENTER_BK_CODE:
            current_setting = (current_setting + 2) % 6;
            break;
        case A_BK_CODE:
            current_setting = (current_setting / 2) * 2;
            break;
        case D_BK_CODE:
            current_setting = (current_setting / 2) * 2 + 1;
            break;
        default:
            break;
    }
}

void settings_mouse_state() {
    if (mouse_info.right_click) {
        // Button 1
        if (mouse_info.x >= 106 && mouse_info.x <= 251 && mouse_info.y >= 260 && mouse_info.y <= 320) {
            current_setting = 0;
        }
        else if (mouse_info.x >= 252 && mouse_info.x <= 396 && mouse_info.y >= 260 && mouse_info.y <= 320) {
            current_setting = 1;
        }

        // Button 2
        else if (mouse_info.x >= 406 && mouse_info.x <= 551 && mouse_info.y >= 260 && mouse_info.y <= 320) {
            current_setting = 2;
        }
        else if (mouse_info.x >= 552 && mouse_info.x <= 698 && mouse_info.y >= 260 && mouse_info.y <= 320) {
            current_setting = 3;
        }

        // Button 3
        else if (mouse_info.x >= 246 && mouse_info.x <= 391 && mouse_info.y >= 402 && mouse_info.y <= 462) {
            current_setting = 4;            
        }
        else if (mouse_info.x >= 392 && mouse_info.x <= 534 && mouse_info.y >= 402 && mouse_info.y <= 462) {
            current_setting = 5;
        }
    }
}

void settings_change_control_device() {
    if (current_setting == 0) {
        controlDevice = MOUSE;
    }
    else if (current_setting == 1) {
        controlDevice = KEYBOARD;
    }
}

void singleplayer_handler() {
    if (controlDevice == KEYBOARD) move_paddle(&mainPaddle); // Avoids delay when using keyboard

    change_ball_pos(&mainBall);
    if (check_ball_out(&mainBall, &mainPaddle)) {
        decreaseLives(&mainBall, &mainPaddle);
        gameState = INIT;
        reset_paddle(&mainPaddle);
        reset_ball(&mainBall);
    }

    if (extra_ball_active()) {
        change_ball_pos(&extraBall);
        if (check_ball_out(&extraBall, &mainPaddle)) {
            disable_extra_ball(&extraBall);
        }
    }

    if (getLives(&mainPaddle) == 0) {
        add_leaderboard_record(current_level, getPoints(), &rtc_time);
        gameState = START;
        reset_game();
    }
    else if (getBrickCounter() == 0) {
        if (current_level == 2) {
            add_leaderboard_record(current_level, getPoints(), &rtc_time);
            current_level = 0;
            reset_game();
        }
        else {
            current_level++;
            reset_ball(&mainBall);
            reset_paddle(&mainPaddle);
            reset_lives();
            counter = 0;
            reset_powerups();
            setup_bricks(levels[current_level]);
        }
    }

    if (counter / 60 == 10) {
        drop_random_powerup();
        counter = 0;
    }
    move_active_powerups();
}

void reset_game() {
    reset_ball(&mainBall);
    reset_paddle(&mainPaddle);
    reset_points();
    reset_lives();
    counter = 0;
    reset_powerups();
    current_level = 0;
    setup_bricks(levels[current_level]);
    gameState = START;
}

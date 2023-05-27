#include "game.h"
#include <lcom/lcf.h>

extern uint8_t scancode;
extern uint8_t packet_counter;
extern uint32_t counter; // Timer counter

SystemState systemState = RUNNING;
GameState gameState = START;
ControlDevice controlDevice =  MOUSE;

extern vbe_mode_info_t mode_info;
extern MouseInfo mouse_info;

extern Paddle mainPaddle;
extern Ball mainBall;
extern Ball extraBall;

void update_keyboard_state() {
    (kbc_ih)();
    switch (gameState) {
    case START:
        switch (scancode) {
        case ESC_BK_CODE:
            systemState = EXIT;
            break;
        case P_BK_CODE:
            gameState = GAME;
            break;
        case H_BK_CODE:
            gameState = SETTINGS;
            break;
        case S_BK_CODE:
            gameState = SCORE;
            break;
    }
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
        case GAME:
            collision_paddle(&mainBall, &mainPaddle);
            move_paddle(&mainPaddle);
            collision_paddle(&mainBall, &mainPaddle);
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
            if (mouse_info.right_click) gameState = GAME;
            if (controlDevice == KEYBOARD) move_paddle_and_ball(&mainPaddle, &mainBall);
            break;
        case GAME:
            timer_int_handler();
            if (controlDevice == KEYBOARD) move_paddle(&mainPaddle); // to avoid scancode waiting
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
            
            if (getBrickCounter() == 0 || getLives(&mainPaddle) == 0) {
                gameState = START;
                reset_game();
            }
            if (counter / 60 == 10) {
                drop_random_powerup();
                counter = 0;
            }
            move_active_powerups();
            
            break;
        default:
            break;
    }
    vg_set_start();
    clear_screen();
    draw_new_frame();
}


void refresh_buttons_state() {
    if (mouse_info.left_click) {
        if (mouse_info.x >= 150 && mouse_info.x <= 150 + 206 && mouse_info.y >= 290 && mouse_info.y <= 290 + 63) {
            gameState = INIT;
        }
        else if (mouse_info.x >= 444 && mouse_info.x <= 444 + 206 && mouse_info.y >= 290 && mouse_info.y <= 290 + 63) {
            gameState = GAME;
        }
        else if (mouse_info.x >= 150 && mouse_info.x <= 150 + 206 && mouse_info.y >= 390 && mouse_info.y <= 390 + 63) {
            gameState = SCORE;
        }
        else if (mouse_info.x >= 444 && mouse_info.x <= 444 + 206 && mouse_info.y >= 390 && mouse_info.y <= 390 + 63) {
            gameState = SETTINGS;
        }
    }
}

void reset_game() {
    reset_ball(&mainBall);
    reset_paddle(&mainPaddle);
    reset_points();
    reset_lives();
    setup_bricks();
}

#include "game.h"
#include <lcom/lcf.h>

extern uint8_t scancode;
extern uint8_t packet_counter;

SystemState systemState = RUNNING;
GameState gameState = START;

extern vbe_mode_info_t mode_info;
extern MouseInfo mouse_info;

extern Paddle mainPaddle;
extern Ball mainBall;

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
        default:
            send_byte(0);
            break;
    }
        break;

    default:
        switch (scancode){
        case ESC_BK_CODE:
            gameState = START;
        default:
            send_byte(0);
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
        case GAME:
            movePaddle(&mainPaddle);
            break;
        default:
            break;
    }
}

void update_timer_state() {
    switch (gameState) {
        case GAME:
            change_ball_pos(&mainBall);
            break;
        default:
            break;
    }
    vg_set_start();
    clear_screen();
    draw_new_frame();
}

void update_sp_state() {
    sp_ih();
    uint8_t byte = pop(get_queue());
    
    printf("%c\n", byte);
    
    }

void refresh_buttons_state() {
    if (mouse_info.left_click) {
        if (mouse_info.x >= 150 && mouse_info.x <= 150 + 206 && mouse_info.y >= 290 && mouse_info.y <= 290 + 63) {
            gameState = GAME;
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

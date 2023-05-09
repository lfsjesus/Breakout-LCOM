#include "model.h"
#include <lcom/lcf.h>

// Variáveis externas importantes à construção e manipulação do modelo
extern uint8_t scancode;
extern uint8_t packet_counter;
SystemState systemState = RUNNING;
GameState gameState = START;
extern vbe_mode_info_t mode_info;
Ball mainBall = {15, 500, 500, 5, 10, 1, 5};

Sprite* mouse;
Sprite* background;
Sprite* button_singleplayer;
Sprite* button_multiplayer;
Sprite* button_leaderboard;
Sprite* button_settings;

void setup_sprites() {
    mouse = create_sprite_xpm((xpm_map_t) mouse_xpm);
    background = create_sprite_xpm((xpm_map_t) menu_background_xpm);
    button_singleplayer = create_sprite_xpm((xpm_map_t) singleplayer_button_xpm);
    button_multiplayer = create_sprite_xpm((xpm_map_t) multiplayer_button_xpm);
    button_leaderboard = create_sprite_xpm((xpm_map_t) leaderboard_button_xpm);
    button_settings = create_sprite_xpm((xpm_map_t) settings_button_xpm);
}

void destroy_sprites() {
  destroy_sprite(mouse);
}

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
}

void update_ball_pos(Ball* ball) {
    int screenWidth = modeinfo.XResolution;
    int screenHeight = modeinfo.YResolution;
    int x = ball->x;
    int y = ball->y;
    x += ball->vx;
    y -= ball->vy;

    // Check if the ball has exceeded the screen limits and adjust accordingly
    
    if (x < 0) {
        x = 0;
        ball->vx *= -1;
    } 
    else if (x + ball->radius > screenWidth) {
        x = screenWidth - ball->radius;
        ball->vx *= -1;
    }

    if (y < 0) {
        y = 0;
        ball->vy *= -1;
    }
    else if (y + ball->radius > screenHeight) {
        y = screenHeight - ball->radius;
        ball->vy *= -1;
    }

    ball->x = x;
    ball->y = y;
}

void update_timer_state() {
    update_ball_pos(&mainBall);
    vg_set_start();
    clear_screen();
    draw_new_frame();
}


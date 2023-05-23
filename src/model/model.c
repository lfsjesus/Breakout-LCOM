#include "model.h"
#include <lcom/lcf.h>

// Variáveis externas importantes à construção e manipulação do modelo
extern uint8_t scancode;
extern uint8_t packet_counter;
SystemState systemState = RUNNING;
GameState gameState = START;
extern vbe_mode_info_t mode_info;
Ball mainBall = {15, 500, 500, 5, 10, 1, 5};
Brick bricks[100] = {{0, 0, 0, 0, 0, 0}};
int brick_counter = 0;

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

void setup_bricks() {
    int width = 70;
    int height = 40;
    int padding = 50;
    int index = 0;
    for (int i = 0; i < 12; i++) {
        for (int j = 0; j < 10; j++) {
            if (map1[i][j] == ' ')
                continue;
            bricks[index].x = padding + j * width;
            bricks[index].y = padding + i * height;
            bricks[index].width = width;
            bricks[index].height = height;
            if (map1[i][j] == 'X') {
                bricks[index].hp = 1;
                bricks[index].color = 0;
                brick_counter++;
            }

            else if (map1[i][j] == 'A') {
                bricks[index].hp = 3;
                bricks[index].color = 1;
                brick_counter++;
            }
            index++;
         }
        }
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
    switch (gameState) {
        case START: 
            refresh_buttons_state();
            break;
        /* Continue */
        default:
            break;
    }
}

void update_timer_state() {
    change_ball_pos(&mainBall);
    vg_set_start();
    clear_screen();
    draw_new_frame();
}


void refresh_buttons_state() {
    if (mouse_info.left_click) {
        if (mouse_info.x >= 150 && mouse_info.x <= 150 + button_singleplayer->width && mouse_info.y >= 290 && mouse_info.y <= 290 + button_singleplayer->height) {
            gameState = GAME;
        }
        else if (mouse_info.x >= 444 && mouse_info.x <= 444 + button_multiplayer->width && mouse_info.y >= 290 && mouse_info.y <= 290 + button_multiplayer->height) {
            gameState = GAME;
        }
        else if (mouse_info.x >= 150 && mouse_info.x <= 150 + button_leaderboard->width && mouse_info.y >= 390 && mouse_info.y <= 390 + button_leaderboard->height) {
            gameState = SCORE;
        }
        else if (mouse_info.x >= 444 && mouse_info.x <= 444 + button_settings->width && mouse_info.y >= 390 && mouse_info.y <= 390 + button_settings->height) {
            gameState = SETTINGS;
        }
    }
}



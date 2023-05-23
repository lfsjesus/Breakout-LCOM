#include "model.h"
#include <lcom/lcf.h>

// Variáveis externas importantes à construção e manipulação do modelo
Sprite* mouse;
Sprite* background;
Sprite* button_singleplayer;
Sprite* button_multiplayer;
Sprite* button_leaderboard;
Sprite* button_settings;

Ball mainBall = {15, 500, 500, 5, 10, 1, 5};

Paddle mainPaddle = {NULL, 300, 500};

Brick bricks[100] = {{0, 0, 0, 0, 0, 0}};
int brick_counter = 0;

void setup_sprites() {
    mouse = create_sprite_xpm((xpm_map_t) mouse_xpm);
    background = create_sprite_xpm((xpm_map_t) menu_background_xpm);
    button_singleplayer = create_sprite_xpm((xpm_map_t) singleplayer_button_xpm);
    button_multiplayer = create_sprite_xpm((xpm_map_t) multiplayer_button_xpm);
    button_leaderboard = create_sprite_xpm((xpm_map_t) leaderboard_button_xpm);
    button_settings = create_sprite_xpm((xpm_map_t) settings_button_xpm);
    mainPaddle.sprite = create_sprite_xpm((xpm_map_t) paddle_xpm);
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






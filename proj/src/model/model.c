#include "model.h"
#include <lcom/lcf.h>

Sprite* mouse;
Sprite* background;
Sprite* button_singleplayer;
Sprite* button_multiplayer;
Sprite* button_leaderboard;
Sprite* button_settings;
Sprite* heart;
Sprite* ball;

Ball mainBall = {NULL, 10, 500, 500, 5, 10, 1, 5};

Paddle mainPaddle = {NULL, 350, 550};

Brick bricks[12][10];

int brick_counter = 0;

void setup_sprites() {
    mouse = create_sprite_xpm((xpm_map_t) mouse_xpm);
    background = create_sprite_xpm((xpm_map_t) menu_background_xpm);
    button_singleplayer = create_sprite_xpm((xpm_map_t) singleplayer_button_xpm);
    button_multiplayer = create_sprite_xpm((xpm_map_t) multiplayer_button_xpm);
    button_leaderboard = create_sprite_xpm((xpm_map_t) leaderboard_button_xpm);
    button_settings = create_sprite_xpm((xpm_map_t) settings_button_xpm);
    mainPaddle.sprite = create_sprite_xpm((xpm_map_t) paddle_xpm);
    heart = create_sprite_xpm((xpm_map_t) heart_xpm);
    mainBall.sprite = create_sprite_xpm((xpm_map_t) ball_xpm);
}

void destroy_sprites() {
    destroy_sprite(mouse);
    destroy_sprite(background);
    destroy_sprite(button_singleplayer);
    destroy_sprite(button_multiplayer);
    destroy_sprite(button_leaderboard);
    destroy_sprite(button_settings);
    destroy_sprite(mainPaddle.sprite);
    destroy_sprite(heart);
}

void setup_bricks() {
    int width = 75;
    int height = 37;
    int padding = 50;
    int start_y = 40;
    for (int i = 0; i < 12; i++) {
        for (int j = 0; j < 10; j++) {
            if (map1[i][j] == ' ') {
                continue;
            }
            bricks[i][j].x = j * width;
            bricks[i][j].y = i * height + start_y + padding;

            if (map1[i][j] == 'X') {
                bricks[i][j].hp = 1;
                bricks[i][j].sprite = create_sprite_xpm((xpm_map_t) bricks_xpm[0]);
                brick_counter++;
            }

            else if (map1[i][j] == 'A') {
                bricks[i][j].hp = 3;
                bricks[i][j].sprite = create_sprite_xpm((xpm_map_t) bricks_xpm[2]);
                brick_counter++;
            }
        }
    }

}







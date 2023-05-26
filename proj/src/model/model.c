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
Sprite* blueBrick;
Sprite* greenBrick;
Sprite* redBrick;
Sprite* blueBrickDamaged;
Sprite* greenBrickDamaged;
Sprite* redBrickDamaged;

Ball mainBall = {NULL, 10, 500, 500, 4, 9, 1, 5};

Paddle mainPaddle = {NULL, 350, 550};

Brick bricks[12][10];

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
    blueBrick = create_sprite_xpm((xpm_map_t) bricks_xpm[0]);
    greenBrick = create_sprite_xpm((xpm_map_t) bricks_xpm[2]);
    redBrick = create_sprite_xpm((xpm_map_t) bricks_xpm[4]);
    blueBrickDamaged = create_sprite_xpm((xpm_map_t) bricks_xpm[1]);
    greenBrickDamaged = create_sprite_xpm((xpm_map_t) bricks_xpm[3]);
    redBrickDamaged = create_sprite_xpm((xpm_map_t) bricks_xpm[5]);
    init_alphabet_sprites();
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
    destroy_sprite(mainBall.sprite);
    destroy_sprite(blueBrick);
    destroy_sprite(greenBrick);
    destroy_sprite(redBrick);
    destroy_sprite(blueBrickDamaged);
    destroy_sprite(greenBrickDamaged);
    destroy_sprite(redBrickDamaged);
    destroy_alphabet_sprites();
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
            bricks[i][j].x = j * (width + 4) + 10;
            bricks[i][j].y = i * height + start_y + padding;

            if (map1[i][j] == 'X') {
                bricks[i][j].hp = 2;
                brick_counter++;
            }

            else if (map1[i][j] == 'B') {
                bricks[i][j].hp = 5;
                brick_counter++;
            }

            else if (map1[i][j] == 'A') {
                bricks[i][j].hp = 9;
                brick_counter++;
            }
        }
    }
}

int getBrickCounter() {
    return brick_counter;
}

void decrementBrickCounter() {
    brick_counter--;
}







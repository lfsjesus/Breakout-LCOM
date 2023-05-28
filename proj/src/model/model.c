#include "model.h"
#include <lcom/lcf.h>

Sprite* mouse;
Sprite* background;
Sprite* settings_backgrounds[6];
Sprite* leaderboard;
Sprite* heart;
Sprite* ball;
Sprite* ball2;
Sprite* paddle;
Sprite* paddle2;
Sprite* extraBallSprite;
Sprite* blueBrick;
Sprite* greenBrick;
Sprite* redBrick;
Sprite* blueBrickDamaged;
Sprite* greenBrickDamaged;
Sprite* redBrickDamaged;
Sprite* ballPowerUpSprite;
Sprite* blockPowerUpSprite;
Sprite* lifePowerUpSprite;

Ball mainBall = {NULL, 10, 500, 500, 4, 9, 1, 5};

Paddle mainPaddle = {NULL, 350, 550};

PowerUp powerUps[3] = {{NULL, 0, 0, 1, false}, {NULL, 0, 0, 2, false}, {NULL, 0, 0, 3, false}};

Brick bricks[12][10];

void setup_sprites() {
    mouse = create_sprite_xpm((xpm_map_t) mouse_xpm);
    background = create_sprite_xpm((xpm_map_t) menu_background_xpm);
    paddle = create_sprite_xpm((xpm_map_t) paddle_xpm);
    paddle2 = create_sprite_xpm((xpm_map_t) paddle2_xpm);
    heart = create_sprite_xpm((xpm_map_t) heart_xpm);
    ball = create_sprite_xpm((xpm_map_t) ball_xpm);
    ball2 = create_sprite_xpm((xpm_map_t) ball2_xpm);
    blueBrick = create_sprite_xpm((xpm_map_t) bricks_xpm[0]);
    greenBrick = create_sprite_xpm((xpm_map_t) bricks_xpm[2]);
    redBrick = create_sprite_xpm((xpm_map_t) bricks_xpm[4]);
    blueBrickDamaged = create_sprite_xpm((xpm_map_t) bricks_xpm[1]);
    greenBrickDamaged = create_sprite_xpm((xpm_map_t) bricks_xpm[3]);
    redBrickDamaged = create_sprite_xpm((xpm_map_t) bricks_xpm[5]);
    ballPowerUpSprite = create_sprite_xpm((xpm_map_t) ball_power_xpm);
    blockPowerUpSprite = create_sprite_xpm((xpm_map_t) block_power_xpm);
    lifePowerUpSprite = create_sprite_xpm((xpm_map_t) life_power_xpm);
    extraBallSprite = create_sprite_xpm((xpm_map_t) extra_ball_xpm);
    settings_backgrounds[0] = create_sprite_xpm((xpm_map_t) controller_mouse_xpm);
    settings_backgrounds[1] = create_sprite_xpm((xpm_map_t) controller_keyboard_xpm);
    settings_backgrounds[2] = create_sprite_xpm((xpm_map_t) ball_option1_xpm);
    settings_backgrounds[3] = create_sprite_xpm((xpm_map_t) ball_option2_xpm);
    settings_backgrounds[4] = create_sprite_xpm((xpm_map_t) paddle_option1_xpm);
    settings_backgrounds[5] = create_sprite_xpm((xpm_map_t) paddle_option2_xpm);
    leaderboard = create_sprite_xpm((xpm_map_t) leaderboard_xpm);
    init_alphabet_sprites();
    init_number_sprites();
}

void destroy_sprites() {
    destroy_sprite(mouse);
    destroy_sprite(background);
    destroy_sprite(paddle);
    destroy_sprite(paddle2);
    destroy_sprite(heart);
    destroy_sprite(ball);
    destroy_sprite(ball2);
    destroy_sprite(blueBrick);
    destroy_sprite(greenBrick);
    destroy_sprite(redBrick);
    destroy_sprite(blueBrickDamaged);
    destroy_sprite(greenBrickDamaged);
    destroy_sprite(redBrickDamaged);
    destroy_sprite(ballPowerUpSprite);
    destroy_sprite(blockPowerUpSprite);
    destroy_sprite(lifePowerUpSprite);
    destroy_sprite(extraBallSprite);
    destroy_sprite(settings_backgrounds[0]);
    destroy_sprite(settings_backgrounds[1]);
    destroy_sprite(settings_backgrounds[2]);
    destroy_sprite(settings_backgrounds[3]);
    destroy_sprite(settings_backgrounds[4]);
    destroy_sprite(settings_backgrounds[5]);
    destroy_sprite(leaderboard);
    destroy_alphabet_sprites();
    destroy_number_sprites();
}

void setup_bricks(char* map[12]) {
    int width = 75;
    int height = 37;
    int padding = 50;
    int start_y = 40;
    for (int i = 0; i < 12; i++) {
        for (int j = 0; j < 10; j++) {
            if (map[i][j] == ' ') {
                continue;
            }
            bricks[i][j].x = j * (width + 4) + 10;
            bricks[i][j].y = i * height + start_y + padding;

            if (map[i][j] == 'X') {
                bricks[i][j].hp = 2;
                brick_counter++;
            }

            else if (map[i][j] == 'B') {
                bricks[i][j].hp = 5;
                brick_counter++;
            }

            else if (map[i][j] == 'A') {
                bricks[i][j].hp = 9;
                brick_counter++;
            }
        }
    }
}

void setup_ball(uint8_t n) {
    if (n == 2) {
        mainBall.sprite = ball;
    }
    else if (n == 3) {
        mainBall.sprite = ball2;
    }
}

void setup_paddle(uint8_t n) {
    if (n == 4) {
        mainPaddle.sprite = paddle;
    }
    else if (n == 5) {
        mainPaddle.sprite = paddle2;
    }
}

void setup_powerups() {
    powerUps[0].sprite = ballPowerUpSprite;
    powerUps[1].sprite = blockPowerUpSprite;
    powerUps[2].sprite = lifePowerUpSprite;
}

int getBrickCounter() {
    return brick_counter;
}

void decrementBrickCounter() {
    brick_counter--;
}



#include "ball.h"

extern vbe_mode_info_t modeinfo;
extern Brick bricks[12][10];
extern Paddle mainPaddle;

void collision_board(Ball* ball) {
    int screenWidth = modeinfo.XResolution;
    int screenHeight = modeinfo.YResolution;
    int minScreenX = 0;
    int minScreenY = 60;

    int16_t ballMinX = ball->x - ball->radius;
    int16_t ballMaxX = ball->x + ball->radius;
    int16_t ballMinY = ball->y - ball->radius;
    int16_t ballMaxY = ball->y + ball->radius;

    if (ballMinX <= minScreenX) {
        ball->vx = -ball->vx;
    } else if (ballMaxX >= screenWidth) {
        ball->vx = -ball->vx;
    } else if (ballMinY <= minScreenY) {
        ball->vy = -ball->vy;
    } else if (ballMaxY >= screenHeight) {
        ball->vy = -ball->vy;
    }
}

void change_ball_pos(Ball* ball) {
    collision_paddle(ball, &mainPaddle);
    collision_board(ball);
    for (int i = 0; i < 12; i++) {
        for (int j = 0; j < 10; j++) {
            if (bricks[i][j].sprite == NULL) continue;
            collision_brick(ball, &bricks[i][j]);
        }
    }
    ball->x += ball->vx;
    ball->y += ball->vy;    
}

void collision_brick(Ball* ball, Brick* brick) {

    int16_t brickMinX = brick->x;
    int16_t brickMaxX = brick->x + brick->sprite->width;
    int16_t brickMinY = brick->y;
    int16_t brickMaxY = brick->y + brick->sprite->height;

    int16_t ballMinX = ball->x - ball->radius;
    int16_t ballMaxX = ball->x + ball->radius;
    int16_t ballMinY = ball->y - ball->radius;
    int16_t ballMaxY = ball->y + ball->radius;

    if (ballMinX <= brickMaxX && ballMaxX >= brickMinX && ballMinY <= brickMaxY && ballMaxY >= brickMinY) {
        if (ball->x >= brickMinX && ball->x <= brickMaxX) {
            ball->vy = -ball->vy;
        } else if (ball->y >= brickMinY && ball->y <= brickMaxY) {
            ball->vx = -ball->vx;
        } else {
            ball->vx = -ball->vx;
            ball->vy = -ball->vy;
        }
        increasePoints();
        brick->sprite = NULL;
    }

}


void collision_paddle(Ball* ball, Paddle* paddle) {
    int16_t paddleMinX = paddle->x;
    int16_t paddleMaxX = paddle->x + paddle->sprite->width;
    int16_t paddleMinY = paddle->y;
    int16_t paddleMaxY = paddle->y + paddle->sprite->height;

    int16_t ballMinX = ball->x - ball->radius;
    int16_t ballMaxX = ball->x + ball->radius;
    int16_t ballMinY = ball->y - ball->radius;
    int16_t ballMaxY = ball->y + ball->radius;

    if (ballMinX <= paddleMaxX && ballMaxX >= paddleMinX && ballMinY <= paddleMaxY && ballMaxY >= paddleMinY) {
        if (ball->x >= paddleMinX && ball->x <= paddleMaxX) {
            ball->vy = -ball->vy;
        } else if (ball->y >= paddleMinY && ball->y <= paddleMaxY) {
            ball->vx = -ball->vx;
        } else {
            ball->vx = -ball->vx;
            ball->vy = -ball->vy;
        }
    }
}

  

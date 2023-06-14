#include "ball.h"

extern vbe_mode_info_t modeinfo;

extern Brick bricks[12][10];
extern Paddle mainPaddle;
extern Ball extraBall;
extern Sprite* extraBallSprite;

void collision_board(Ball* ball) {
    int screenWidth = modeinfo.XResolution;
    int screenHeight = modeinfo.YResolution;
    int minScreenX = 0;
    int minScreenY = 60;

    int16_t ballMinX = ball->x - 2;
    int16_t ballMaxX = ball->x + ball->sprite->width + 2;
    int16_t ballMinY = ball->y - 2;
    int16_t ballMaxY = ball->y + ball->sprite->height;

    if (ballMinX <= minScreenX) {
        ball->vx = -ball->vx;
    } else if (ballMaxX >= screenWidth) {
        ball->vx = -ball->vx;
    } 
    if (ballMinY <= minScreenY) {
        ball->vy = -ball->vy;
    } else if (ballMaxY >= screenHeight) {
        ball->vy = -ball->vy;
    }
}

void change_ball_pos(Ball* ball) {
    collision_board(ball); 
    collision_paddle(ball, &mainPaddle);
    check_powerup_collision(&mainPaddle);
    collision_extra_ball(ball, &extraBall); 
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
    int16_t ballMaxX = ball->x + ball->sprite->width;
    int16_t ballMinY = ball->y - ball->radius;
    int16_t ballMaxY = ball->y + ball->sprite->height;

    if (ballMinX <= brickMaxX && ballMaxX >= brickMinX && ballMinY <= brickMaxY && ballMaxY >= brickMinY) {
        if (ball->x >= brickMinX && ball->x <= brickMaxX) {
            ball->vy = -ball->vy;
        } else if (ball->y >= brickMinY && ball->y <= brickMaxY) {
            ball->vx = -ball->vx;
        } else {
            ball->vx = -ball->vx;
            ball->vy = -ball->vy;
        }
        increase_points();
        decrease_hp(brick);
    }    
}


void collision_paddle(Ball* ball, Paddle* paddle) {
    int16_t paddleMinX = paddle->x;
    int16_t paddleMaxX = paddle->x + paddle->sprite->width;
    int16_t paddleMinY = paddle->y;
    int16_t paddleMaxY = paddle->y + paddle->sprite->height;

    int16_t ballMinX = ball->x - 2;
    int16_t ballMaxX = ball->x + ball->sprite->width;
    int16_t ballMinY = ball->y - 2;
    int16_t ballMaxY = ball->y + ball->sprite->height;

    if (ballMinX <= paddleMaxX && ballMaxX >= paddleMinX && ballMinY <= paddleMaxY && ballMaxY >= paddleMinY) {
        if (ball->x >= paddleMinX && ball->x <= paddleMaxX) {
            ball->vy = -ball->vy;
        } else if (ball->y >= paddleMinY && ball->y <= paddleMaxY) {
            ball->vx = -ball->vx;

        } else {
            ball->vx = -ball->vx;
            ball->vy = -ball->vy;
        }

        // Ins the ball is stuck inside the paddle
        if (ball->y > paddleMinY && ballMinY < paddleMaxY) {
            if (ball->y < paddle->y) {
                ball->y = paddle->y - ball->radius;
            } else {
                ball->y = paddleMaxY + ball->radius;
            }
        }
    }
}

void collision_extra_ball(Ball* ball, Ball* extraBall) {
    int16_t ballMinX = ball->x - 2;
    int16_t ballMaxX = ball->x + ball->sprite->width + 2;
    int16_t ballMinY = ball->y - 2;
    int16_t ballMaxY = ball->y + ball->sprite->height + 2;

    if (!extra_ball_active()) return;

    if (ballMinX <= extraBall->x && ballMaxX >= extraBall->x && ballMinY <= extraBall->y && ballMaxY >= extraBall->y) {
        if (ball->x >= extraBall->x && ball->x <= extraBall->x) {
            ball->vy = -ball->vy;
            extraBall->vy = -extraBall->vy;
        } else if (ball->y >= extraBall->y && ball->y <= extraBall->y) {
            ball->vx = -ball->vx;
            extraBall->vx = -extraBall->vx;
        } else {
            ball->vx = -ball->vx;
            ball->vy = -ball->vy;
            extraBall->vx = -extraBall->vx;
            extraBall->vy = -extraBall->vy;
        }
    }
}

bool check_ball_out(Ball* ball, Paddle* paddle) {
    if (ball->y >= modeinfo.YResolution - ball->sprite->height - 2) {
        return true;
    }
    return false;
}

void add_ball(Ball* mainBall, Ball* newBall) {
    newBall->x = (mainBall->x + 30) % modeinfo.XResolution;
    newBall->y = mainBall->y;
    newBall->vx = mainBall->vx;
    newBall->vy = mainBall->vy;
    newBall->radius = mainBall->radius;
    newBall->sprite = extraBallSprite;
}

void reset_ball(Ball* ball) {
    ball->x = (mainPaddle.x + (mainPaddle.sprite->width / 2 - ball->radius));
    ball->y = (mainPaddle.y - ball->sprite->height);
    ball->vx = 4;
    ball->vy = 7;
}

void disable_extra_ball(Ball* ball) {
    ball->sprite = NULL;
}

  

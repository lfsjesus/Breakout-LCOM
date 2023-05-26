#include "paddle.h"
#include <lcom/lcf.h>
extern struct packet mouse_packet;
extern vbe_mode_info_t modeinfo;

static int playerPoints = 0;
static int lives = 3;

int getPoints() {
    return playerPoints;
}

int getLives() {
    return lives;
}

void move_paddle(Paddle* paddle) {
    int max_speed = 8;

    if (mouse_packet.delta_x > 0) {
        if (paddle->x + paddle->sprite->width + mouse_packet.delta_x < modeinfo.XResolution) {
            paddle->x += (mouse_packet.delta_x > max_speed) ? max_speed : mouse_packet.delta_x;
        }
    }
    else if (mouse_packet.delta_x < 0) {
        if (paddle->x + mouse_packet.delta_x > 0) {
            paddle->x += (mouse_packet.delta_x < -max_speed) ? -max_speed : mouse_packet.delta_x;
        }
    }
}

void move_paddle_and_ball(Paddle* paddle, Ball* ball) {
    move_paddle(paddle);
    ball->x = paddle->x + paddle->sprite->width / 2 - ball->sprite->width / 2;
    ball->y = paddle->y - ball->sprite->height;
}

void increase_points() {
    playerPoints++;
}

void decreaseLives() {
    lives--;
}

void reset_paddle(Paddle* paddle) {
    paddle->x = 350;
    paddle->y = 550;
}

void reset_points() {
    playerPoints = 0;
}

#include "paddle.h"
#include <lcom/lcf.h>
extern struct packet mouse_packet;
extern uint8_t scancode;
extern vbe_mode_info_t modeinfo;
extern ControlDevice controlDevice;
static int playerPoints = 0;
static int lives = 3;
static uint8_t max_speed = 8;

int getPoints() {
    return playerPoints;
}

int getLives() {
    return lives;
}

void mouse_move_paddle(Paddle* paddle) {
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

void keyboard_move_paddle(Paddle* paddle) {
    max_speed = 10;
    if (scancode == A_MK_CODE) {
        if (paddle->x - max_speed > 0) {
            paddle->x -= max_speed;
        }
        else {
            paddle->x = 0;
        }
    }
    else if (scancode == D_MK_CODE) {
        if (paddle->x + paddle->sprite->width + max_speed < modeinfo.XResolution) {
            paddle->x += max_speed;
        }
        else {
            paddle->x = modeinfo.XResolution - paddle->sprite->width;
        }
    }
}

void move_paddle(Paddle* paddle) {
    switch(controlDevice) {
        case MOUSE:
            mouse_move_paddle(paddle);
            break;
        case KEYBOARD:
            keyboard_move_paddle(paddle);
            break;
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

void increaseLives() {
    lives++;
}

void reset_paddle(Paddle* paddle) {
    paddle->x = 350;
    paddle->y = 550;
}

void reset_points() {
    playerPoints = 0;
}

void reset_lives() {
    lives = 3;
}

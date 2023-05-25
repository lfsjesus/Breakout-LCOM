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

void movePaddle(Paddle* paddle) {
    if (mouse_packet.delta_x > 0) {
        if (paddle->x + paddle->sprite->width + mouse_packet.delta_x < modeinfo.XResolution) {
            paddle->x += mouse_packet.delta_x;
        }
    }
    else if (mouse_packet.delta_x < 0) {
        if (paddle->x + mouse_packet.delta_x > 0) {
            paddle->x += mouse_packet.delta_x;
        }
    }
}

void increasePoints() {
    playerPoints++;
}


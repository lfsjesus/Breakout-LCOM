#include "paddle.h"
#include <lcom/lcf.h>
extern struct packet mouse_packet;
extern vbe_mode_info_t modeinfo;

void movePaddle(Paddle* paddle) {
    if (mouse_packet.delta_x > 0) {
        if (paddle->x + paddle->sprite->width + mouse_packet.delta_x < modeinfo.XResolution) {
            paddle->x += mouse_packet.delta_x;
        }
        else {
            paddle->x = modeinfo.XResolution - paddle->sprite->width;
        }
    }
    else if (mouse_packet.delta_x < 0) {
        if (paddle->x + mouse_packet.delta_x > 0) {
            paddle->x += mouse_packet.delta_x;
        }
        else {
            paddle->x = 0;
        }
    }
}

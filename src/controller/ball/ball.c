#include "ball.h"
#include <lcom/lcf.h>

extern vbe_mode_info_t modeinfo;

void change_ball_pos(Ball* ball) {

    int screenWidth = modeinfo.XResolution;
    int screenHeight = modeinfo.YResolution;
    int x = ball->x;
    int y = ball->y;
    x += ball->vx;
    y -= ball->vy;

    
    if (x < 0) {
        x = 0;
        ball->vx *= -1;
    } 
    else if (x + ball->radius > screenWidth) {
        x = screenWidth - ball->radius;
        ball->vx *= -1;
    }

    if (y < 0) {
        y = 0;
        ball->vy *= -1;
    }
    else if (y + ball->radius > screenHeight) {
        y = screenHeight - ball->radius;
        ball->vy *= -1;
    }

    ball->x = x;
    ball->y = y;
}

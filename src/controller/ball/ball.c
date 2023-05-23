#include "ball.h"
#include <lcom/lcf.h>

extern vbe_mode_info_t modeinfo;
extern Brick bricks[100];


void collision_board(Ball* ball) {
  
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

void change_ball_pos(Ball* ball) {

  collision_board(ball);

  for (int i = 0; i < 100; i++) {
    Brick* actual = &bricks[i];
    if (actual->width == 0)
      continue;
    collision_brick(ball, actual);
  }
}

void collision_brick(Ball* ball, Brick* brick) {
    int16_t ballMinX = ball->x - ball->radius;
    int16_t ballMaxX = ball->x + ball->radius;
    int16_t ballMinY = ball->y - ball->radius;
    int16_t ballMaxY = ball->y + ball->radius;

    int16_t brickMinX = brick->x;
    int16_t brickMaxX = brick->x + brick->width;
    int16_t brickMinY = brick->y;
    int16_t brickMaxY = brick->y + brick->height;

    if (ballMaxX >= brickMinX && ballMinX <= brickMaxX && ballMaxY >= brickMinY && ballMinY <= brickMaxY) {
        // Calculate the center of the brick
        int16_t brickCenterX = brickMinX + brick->width / 2;
        int16_t brickCenterY = brickMinY + brick->height / 2;

        // Calculate the distance between the ball's center and the brick's center
        int16_t distanceX = ball->x - brickCenterX;
        int16_t distanceY = ball->y - brickCenterY;


        // Check which side of the brick the ball collided with
        if (abs(distanceX) >= abs(distanceY)) {
            // Collided horizontally
            if (distanceX > 0) {
                ball->x = brickMaxX + ball->radius;
            } else {
                ball->x = brickMinX - ball->radius;
            }
            ball->vx = -ball->vx;
        } else {
            // Collided vertically
            if (distanceY > 0) {
                ball->y = brickMaxY + ball->radius;
            } else {
                ball->y = brickMinY - ball->radius;
            }
            ball->vy = -ball->vy;
        }

        brick->color++;
        brick->color %= 2;
    }
}
  

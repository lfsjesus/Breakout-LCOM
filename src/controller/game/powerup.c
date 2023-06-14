#include "powerup.h"

extern PowerUp powerUps[3];
extern Ball mainBall;
Ball extraBall;

void drop_random_powerup() {
    int random = rand() % 3;
    
    int randomX = rand() % 770;
    int randomY = rand() % 450 + 100;

    powerUps[random].x = randomX;
    powerUps[random].y = randomY;
    powerUps[random].active = true;
}

void disable_powerup(PowerUp *powerup) {
    powerup->active = false;
}

void move_active_powerups() {
    for (int i = 0; i < 3; i++) {
        if (powerUps[i].active) {
            powerUps[i].y += 2;
        }
        if (powerUps[i].y >= 600) {
            disable_powerup(&powerUps[i]);
        }
    }
}

void activate_powerup(PowerUp *powerup) {
    switch (powerup->type) {
        case 1:
            add_ball(&mainBall, &extraBall);
            break;
        case 2:
            destroy_red_bricks();
            break;
        case 3:
            increaseLives();
            break;
        default:
            break;
    }
    disable_powerup(powerup);
}

void check_powerup_collision(Paddle *paddle) {
    for (int i = 0; i < 3; i++) {
        if (powerUps[i].active) {
            if (powerUps[i].x + powerUps[i].sprite->width >= paddle->x && powerUps[i].x <= paddle->x + paddle->sprite->width && powerUps[i].y + powerUps[i].sprite->height >= paddle->y && powerUps[i].y <= paddle->y + paddle->sprite->height) {
                activate_powerup(&powerUps[i]);
            }
        }
    }
}

bool extra_ball_active() {
  return extraBall.sprite != NULL;
}

void reset_powerups() {
  for (int i = 0; i < 3; i++) {
    powerUps[i].active = false;
  }
  disable_extra_ball(&extraBall);
}



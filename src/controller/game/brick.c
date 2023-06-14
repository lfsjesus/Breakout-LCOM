#include "brick.h"
#include <lcom/lcf.h>

extern Brick bricks[12][10];

void decrease_hp(Brick* brick) {
  brick->hp -= 1;
  if (brick->hp == 0) {
    brick->sprite = NULL;   
    decrementBrickCounter();
  }
}

void destroy_red_bricks() {
  // Power up that removes 4 hp to red bricks
  for (int i = 0; i < 12; i++) {
    for (int j = 0; j < 10; j++) {
      if (bricks[i][j].hp > 6 && bricks[i][j].hp <= 9) {
        bricks[i][j].hp -= 4;
      } 
    }
  }
}





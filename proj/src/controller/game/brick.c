#include "brick.h"
#include <lcom/lcf.h>

void decrease_hp(Brick* brick) {
  brick->hp -= 1;
  if (brick->hp == 0) {
    brick->sprite = NULL;   
    decrementBrickCounter();
  }

}





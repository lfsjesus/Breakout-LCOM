#include "brick.h"
#include <lcom/lcf.h>

void change_hp(Brick* brick) {
  brick->hp -= 1;
}

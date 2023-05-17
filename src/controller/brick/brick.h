#ifndef BRICK
#define BRICK

#include "stdlib.h"
#include "stdio.h"

typedef struct {
    uint16_t x;
    uint16_t y;
    uint16_t width;
    uint16_t height;
    uint8_t hp;
    uint8_t color;
}Brick;

void change_hp(Brick* brick);

#endif

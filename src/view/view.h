#ifndef _LCOM_VIEW_H_
#define _LCOM_VIEW_H_

#include <minix/sysutil.h>
#include <lcom/lcf.h>
#include "../controller/video/graphics.h"
#include "../controller/keyboard_mouse/mouse.h"
#include "../model/sprite.h"
#include "../model/model.h"
#include "../controller/ball/ball.h"
#include "../controller/brick/brick.h"

#define TRANSPARENT 0xFFFFFE

void draw_mouse();

void draw_menu();

void draw_ball();

void draw_bricks();

int draw_sprite_xpm(Sprite *sprite, int x, int y);

void draw_new_frame();

void clear_screen();

#endif

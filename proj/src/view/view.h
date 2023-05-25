#ifndef _LCOM_VIEW_H_
#define _LCOM_VIEW_H_

#include <minix/sysutil.h>
#include <lcom/lcf.h>
#include "../controller/video/graphics.h"
#include "../controller/keyboard_mouse/mouse.h"
#include "../model/sprite.h"
#include "../controller/game/game.h"
#include "../model/xpm/font/font.h"

#define TRANSPARENT 0xFFFFFE

void draw_mouse();

void draw_menu();

void draw_ball();

void draw_bricks();

void draw_points();

void draw_lives();

void draw_text(char *text, int x, int y);

int draw_sprite_xpm(Sprite *sprite, int x, int y);

void draw_new_frame();

void clear_screen();

#endif

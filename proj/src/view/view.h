#ifndef _LCOM_VIEW_H_
#define _LCOM_VIEW_H_

#include <minix/sysutil.h>
#include <lcom/lcf.h>
#include "../controller/video/graphics.h"
#include "../controller/keyboard_mouse/mouse.h"
#include "../model/sprite.h"
#include "../controller/game/game.h"
#include "../controller/game/leaderboard.h"
#include "../model/xpm/font/font.h"

#define TRANSPARENT 0xFFFFFE

void draw_mouse();

void draw_ball();

void draw_bricks();

void draw_points();

void draw_lives();

void draw_active_powerups();

void draw_setting_screen();

void draw_leaderboard_screen();

void draw_leaderboard_records(LeaderboardRecord* records);

void draw_instruction();

void draw_text(char *text, uint16_t x, uint16_t y);

int draw_scaled_sprite_xpm(Sprite *sprite, int x, int y);

int draw_sprite_xpm(Sprite *sprite, int x, int y);

void draw_new_frame();

void clear_screen();

#endif

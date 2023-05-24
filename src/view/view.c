#include "view.h"
#include <lcom/lcf.h>

extern MouseInfo mouse_info;
extern Ball mainBall;
extern Brick bricks[100];
extern Paddle mainPaddle;

extern GameState gameState;

extern Sprite *mouse;
extern Sprite *background;
extern Sprite *button_singleplayer;
extern Sprite *button_multiplayer;
extern Sprite *button_leaderboard;
extern Sprite *button_settings;
extern Sprite *paddle;

int draw_sprite_xpm(Sprite *sprite, int x, int y) {
  uint16_t height = sprite->height;
  uint16_t width = sprite->width;
  uint32_t current_color;
  for (int h = 0; h < height; h++) {
    for (int w = 0; w < width; w++) {
      current_color = sprite->colors[w + h * width];
      if (current_color == TRANSPARENT)
        continue;
      if (vg_draw_pixel(x + w, y + h, current_color) != 0)
        return 1;
    }
  }
  return 0;
}

void draw_mouse() {
  draw_sprite_xpm(mouse, mouse_info.x, mouse_info.y);
}

void draw_menu() {
  draw_sprite_xpm(button_singleplayer, 150, 290);
  draw_sprite_xpm(button_multiplayer, 444, 290);
  draw_sprite_xpm(button_leaderboard, 150, 390);
  draw_sprite_xpm(button_settings, 444, 390);

}

void draw_ball() {
  vg_draw_rectangle(mainBall.x, mainBall.y, mainBall.radius, mainBall.radius, 0xFFFFFF);
}

void draw_paddle() {
  draw_sprite_xpm(mainPaddle.sprite, mainPaddle.x, mainPaddle.y);
}

void draw_bricks() {
  int colors[2] = {0xFF0000, 0x0000FF};
  vg_draw_rectangle(bricks[0].x, bricks[0].y, bricks[0].width, bricks[0].height, colors[bricks[0].color]);

  for (int i = 0; i < 100; i++) {
    if (bricks[i].width == 0)
      break;

    vg_draw_rectangle(bricks[i].x, bricks[i].y, bricks[i].width, bricks[i].height, colors[bricks[i].color]);
  }
}

void draw_new_frame() {
  switch (gameState){
  case START:
    draw_menu();
    draw_mouse();
    break;
  
  case SETTINGS:
     vg_draw_rectangle(100, 100, 10, 10, 0xFF0000);
    break;
  
  case SCORE:
    vg_draw_rectangle(100, 100, 10, 10, 0x00FF00);
    break;
  
  case GAME:
    draw_paddle();
    draw_bricks();
    draw_ball();
    break;
  default:
    break;
  }

}

void clear_screen() {
  switch (gameState){
  case START:
    draw_sprite_xpm(background, 0, 0);
    break;
  
  default:
    vg_draw_rectangle(0, 0, modeinfo.XResolution, modeinfo.YResolution, 0);
    break;
  }
}

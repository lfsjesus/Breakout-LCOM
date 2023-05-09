#include "view.h"
#include <lcom/lcf.h>

extern MouseInfo mouse_info;
extern SystemState systemState;
extern GameState gameState;
extern Ball mainBall;
extern Sprite *mouse;
extern Sprite *background;
extern Sprite *button_singleplayer;
extern Sprite *button_multiplayer;
extern Sprite *button_leaderboard;
extern Sprite *button_settings;

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

void draw_level() {
  int width = 70;
  int height = 30;
  int padding = 50;
  for (int i = 0; i < 8; i++)
    for (int j = 0; j < 10; j++) {
      if (maps1[i][j] == 'X')
        vg_draw_rectangle(padding + width * j, padding + i * height, width, height, 0xFF0200); // substituir por xpm
      else if (maps1[i][j] == 'A')
        vg_draw_rectangle(padding + width * j, padding + i * height, width, height, 0x0000FF);

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
    draw_level();
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

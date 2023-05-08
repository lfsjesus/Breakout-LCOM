#include "view.h"
#include <lcom/lcf.h>

extern MouseInfo mouse_info;
extern SystemState systemState;
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
  draw_sprite_xpm(background, 0, 0);
  draw_sprite_xpm(button_singleplayer, 150, 290);
  draw_sprite_xpm(button_multiplayer, 444, 290);
  draw_sprite_xpm(button_leaderboard, 150, 390);
  draw_sprite_xpm(button_settings, 444, 390);

}

void draw_new_frame() {
  draw_mouse();
}

void clear_screen() {
  draw_menu();
}

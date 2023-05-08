#include "view.h"
#include <lcom/lcf.h>

extern MouseInfo mouse_info;

extern Sprite *mouse;

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

void draw_new_frame() {
  clear_vram();
  draw_mouse();
}

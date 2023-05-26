#include "view.h"
#include <lcom/lcf.h>

extern MouseInfo mouse_info;
extern Ball mainBall;
extern Brick bricks[12][10];
extern Paddle mainPaddle;

extern GameState gameState;

extern Sprite *mouse;
extern Sprite *background;
extern Sprite *button_singleplayer;
extern Sprite *button_multiplayer;
extern Sprite *button_leaderboard;
extern Sprite *button_settings;
extern Sprite *paddle;
extern Sprite *heart;

int draw_sprite_xpm(Sprite *sprite, int x, int y) {
  uint16_t height = sprite->height;
  uint16_t width = sprite->width;
  uint32_t current_color;
  for (int h = 0; h < height; h++) {
    for (int w = 0; w < width; w++) {
      current_color = sprite->colors[w + h * width];
      if (current_color == TRANSPARENT)
        continue;
      if (x + w >= modeinfo.XResolution || y + h >= modeinfo.YResolution)
        return 1;
      memcpy(frame_buffer + buffer_index * frame_size + (modeinfo.XResolution * (y + h) + (x + w)) * bytes_per_pixel, &sprite->colors[w + h * width], bytes_per_pixel);

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
  draw_sprite_xpm(mainBall.sprite, mainBall.x, mainBall.y);
}

void draw_paddle() {
  draw_sprite_xpm(mainPaddle.sprite, mainPaddle.x, mainPaddle.y);
}

void draw_bricks() {
  for (int i = 0; i < 12; i++) {
    for (int j = 0; j < 10; j++) {
      if (bricks[i][j].sprite == NULL)
        continue;
      draw_sprite_xpm(bricks[i][j].sprite, bricks[i][j].x, bricks[i][j].y);
    }
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
    draw_points();
    draw_lives();
    draw_paddle();
    draw_bricks();
    draw_ball();
    
    break;
  default:
    break;
  }

}

void draw_points() {
  int points = getPoints();
  
  int spacing = 31;
  int i = 3; 

  for (int j = 0; j < 4; j++) {
    uint16_t digit = points % 10;
    points /= 10;
    draw_sprite_xpm(create_sprite_xpm(digits[digit]), i * spacing, 0); 
    i--;
  }
}

void draw_text(char *text, int x, int y) {
  int spacing = 31;
  int i = 0;

  while (text[i] != '\0') {
    if (text[i] == ' ')
      x += spacing;
    else {
    draw_sprite_xpm(create_sprite_xpm(alphabet[text[i] - 'A']), x + i * spacing, y);
    }
    i++;
  }
}

void draw_lives() {
  int lives = getLives();
  int spacing = 65;
  int startX = 800 - (lives * spacing);

  for (int i = 0; i < lives; i++) {
    draw_sprite_xpm(heart, startX + i * spacing, 0);
  }
}

void clear_screen() {
  switch (gameState){
  case START:
    draw_sprite_xpm(background, 0, 0);
    break;
  
  default:
    memset(frame_buffer + buffer_index * frame_size, 0, (size_t) frame_size);
    break;
  }
}

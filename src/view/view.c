#include "view.h"
#include <lcom/lcf.h>

extern MouseInfo mouse_info;
extern MouseInfo guest_mouse_info;
extern Ball mainBall;
extern Ball extraBall;
extern Brick bricks[12][10];
extern Paddle mainPaddle;
extern Paddle guestPaddle;
extern PowerUp powerUps[3];

extern AppState gameState;

extern Sprite* settings_backgrounds[6];
extern Sprite* leaderboard;
extern Sprite* mouse;
extern Sprite* background;
extern Sprite* paddle;
extern Sprite* heart;
extern Sprite* blueBrick;
extern Sprite* greenBrick;
extern Sprite* redBrick;
extern Sprite* blueBrickDamaged;
extern Sprite* greenBrickDamaged;
extern Sprite* redBrickDamaged;

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
      memcpy(frame_buffer + buffer_index * frame_size + (modeinfo.XResolution * (y + h) + (x + w)) * bytes_per_pixel, &current_color, bytes_per_pixel);

    }
  }
  return 0;
}

void draw_mouse() {
  draw_sprite_xpm(mouse, mouse_info.x, mouse_info.y);
}

void draw_ball() {
  draw_sprite_xpm(mainBall.sprite, mainBall.x, mainBall.y);
}

void draw_extra_ball() {
  if (extraBall.sprite != NULL)
    draw_sprite_xpm(extraBall.sprite, extraBall.x, extraBall.y);
}

void draw_paddle() {
  draw_sprite_xpm(mainPaddle.sprite, mainPaddle.x, mainPaddle.y);
}

void draw_guest_paddle() {
  draw_sprite_xpm(mainPaddle.sprite, guest_mouse_info.x, guestPaddle.y);
  //printf("GUEST-> %d; %d\n", guest_mouse_info.x, guest_mouse_info.y);
}

void draw_bricks() {
  for (int i = 0; i < 12; i++) {
    for (int j = 0; j < 10; j++) {
      if (bricks[i][j].sprite == NULL && bricks[i][j].hp == 0)
        continue;

      if (bricks[i][j].hp == 2) {
        bricks[i][j].sprite = blueBrick;
      }

      else if (bricks[i][j].hp == 1) {
        bricks[i][j].sprite = blueBrickDamaged;
      }

      else if (bricks[i][j].hp == 5) {
        bricks[i][j].sprite = greenBrick;
      }

      else if (bricks[i][j].hp == 3) {
        bricks[i][j].sprite = greenBrickDamaged;
      }

      else if (bricks[i][j].hp == 9) {
        bricks[i][j].sprite = redBrick;
      }

      else if (bricks[i][j].hp == 6) {
        bricks[i][j].sprite = redBrickDamaged;
      }

      draw_sprite_xpm(bricks[i][j].sprite, bricks[i][j].x, bricks[i][j].y);
    }
  }
}

void draw_new_frame() {
  switch (gameState){

    case START:
      break;
    case SETTINGS:
      draw_setting_screen();
      break;
    case LEADERBOARD:
      draw_leaderboard_screen();
      draw_leaderboard_records(get_records());
      break;
    case INIT:
      draw_instruction();
    case SINGLEPLAYER:
      draw_points();
      draw_lives();
      draw_paddle();
      draw_bricks();
      draw_ball();
      draw_extra_ball();
      draw_active_powerups();
      break;
    case MULTIPLAYER:
      draw_guest_paddle();
      draw_paddle();
    default:
      break;
  }
  if (get_control_device() == MOUSE && gameState != INIT  && gameState != SINGLEPLAYER) {
    draw_mouse();  
  }
}

void draw_setting_screen() {
  draw_sprite_xpm(settings_backgrounds[get_current_setting()], 0, 0);
}

void draw_leaderboard_screen() {
  draw_sprite_xpm(leaderboard, 0, 0);
}

void draw_points() {
  int points = getPoints();
  
  int spacing = 28;
  int i = 3; 

  for (int j = 0; j < 4; j++) {
    uint16_t digit = points % 10;
    points /= 10;
    Sprite* number = get_number(digit + '0');
    draw_sprite_xpm(number, i * spacing, 5); 
    i--;
  }
}

void draw_instruction() {
  draw_text("MOVE AND SHOOT", 250, 470);
}

void draw_text(char *text, uint16_t x, uint16_t y) {
  int i = 0;
  
  while (text[i] != '\0') {
    if (text[i] >= 'A' && text[i] <= 'Z') {
      Sprite* letter = get_char(text[i]);
      draw_sprite_xpm(letter, x, y);
      x += letter->width;
    }
    else if (text[i] >= '0' && text[i] <= '9') {
      Sprite* number = get_number(text[i]);
      draw_sprite_xpm(number, x, y);
      x += number->width;
    }
    else if (text[i] == ':') {
      draw_sprite_xpm(twoPoints, x, y);
      x += twoPoints->width;
    }
    else if (text[i] == '/') {
      draw_sprite_xpm(slashSprite, x, y);
      x += slashSprite->width;
    }
    else {
      x += 10;
    }
    i++;
  }
}

void draw_leaderboard_records(LeaderboardRecord* records) {
  for (int i = 0; i < get_entries_filled(); i++) {
    draw_text(records[i].row_content, 150, 215 + 65 * i);    
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

void draw_active_powerups() {
  for (int i = 0; i < 3; i++) {
    if (powerUps[i].active) {
      draw_sprite_xpm(powerUps[i].sprite, powerUps[i].x, powerUps[i].y);
    }
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

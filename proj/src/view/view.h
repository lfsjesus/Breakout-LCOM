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

/**
 * @brief Draws the sprite for the mouse
 */
void draw_mouse();
/**
 * @brief Draws the sprite for the ball
 */
void draw_ball();
/**
 * @brief Draws the sprites for all the bricks 
 * according to brick's HP (health-points)
 */
void draw_bricks();
/**
 * @brief Draws the sprite for the points (all digits)
 */
void draw_points();
/**
 * @brief Draws the sprite for the lives of the player
 */
void draw_lives();
/**
 * @brief Draws the sprite for all the powerups that are active
 */
void draw_active_powerups();
/**
 * @brief Draws the sprite for the settings screen
 */
void draw_setting_screen();


/**
 * @brief Draws the sprite for the leaderboard over screen
 *
 */
void draw_leaderboard_screen();

/**
 * @brief Draws the sprite for the leaderboard records
 * @param records array of leaderboard records
 */
void draw_leaderboard_records(LeaderboardRecord* records);

/**
 * @brief Draws the sprite for the game instructions
 */
void draw_instruction();

/**
 * @brief Draws the sprite for text
 * @param text text to draw
 * @param x x-coordinate to draw
 * @param y y-coordinate to draw
 */
void draw_text(char *text, uint16_t x, uint16_t y);

/**
 * @brief Draws sprite xpm
 * @param sprite pointer to the sprite to draw
 * @param x x-coordinate to draw
 * @param y y-coordinate to draw
 * @return int (0 on success and 1 on failure)
 */
int draw_sprite_xpm(Sprite *sprite, int x, int y);

/**
 * @brief Draws the frame according to the game state
 */
void draw_new_frame();

/**
 * @brief Clears the screen
 */
void clear_screen();

#endif

#ifndef __GRAPHICS_H
#define __GRAPHICS_H

#include <lcom/lcf.h>
#include "VBE.h"

/**
 * @brief Changes the mode to graphics mode 
 * @return int - 0 on success and 1 on failure
 */
int (set_graphics_mode)(uint16_t mode);

/**
 * @brief Changes the mode to text mode 
 * @return int - 0 on success and 1 on failure
 */
int (set_text_mode)();

/**
 * @brief Builds the phisical and virtual frame buffer
 * @param mode - mode to be used
 * @return int - 0 on success and 1 on failure
 */
int (set_frame_buffer)(uint16_t mode);

/**
 * @brief Changes the color of a pixel
 * @param x x-coordinate of the pixel
 * @param y y-coordinate of the pixel
 * @param color color to paint the pixel
 * @return int - 0 on success and 1 on failure
 */
int (vg_draw_pixel)(uint16_t x, uint16_t y, uint32_t color);

/**
 * @brief Draws a horizontal line with a specific color
 * @param x x-coordinate to start
 * @param y y-coordinate to start
 * @param len lenght of the line
 * @param color color to paint the line
 * @return int - 0 on success and 1 on failure
 */
int (vg_draw_hline)(uint16_t x, uint16_t y, uint16_t len, uint32_t color);

/**
 * @brief Draws a rectangle with a specific color
 * @param x x-coordinate to start
 * @param y y-coordinate to start
 * @param width width of the rectangle
 * @param height height of the rectangle
 * @param color color to paint the rectangle
 * @return int - 0 on success and 1 on failure
 */
int (vg_draw_rectangle)(uint16_t x, uint16_t
 y, uint16_t width, uint16_t height, uint32_t color);


/**
 * @brief Defines where the VRAM starts
 * @return int - 0 on success and 1 on failure
 */
int (vg_set_start) ();

/**
 * @brief variable that stores information about the mode
 */
vbe_mode_info_t modeinfo;

/**
 * @brief variable that stores the frame buffer
 */
uint8_t* frame_buffer;

/**
 * @brief variable that stores the buffer index
 */
unsigned buffer_index;

/**
 * @brief variable that stores the number of bytes per pixel
 */
unsigned bytes_per_pixel;

/**
 * @brief variable that stores the frame size
 */
unsigned frame_size;

#endif

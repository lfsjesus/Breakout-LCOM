#ifndef __GRAPHICS_H
#define __GRAPHICS_H

#include <lcom/lcf.h>
#include "VBE.h"

int (set_graphics_mode)(uint16_t mode);

int (set_text_mode)();

int (set_frame_buffer)(uint16_t mode);

int (vg_draw_pixel)(uint16_t x, uint16_t y, uint32_t color);

int (vg_draw_hline)(uint16_t x, uint16_t y, uint16_t len, uint32_t color);

int (vg_draw_rectangle)(uint16_t x, uint16_t
 y, uint16_t width, uint16_t height, uint32_t color);

int (normalize_color)(uint32_t color, uint32_t *new_color);

int (vg_set_start) ();

void (clear_vram) ();

int (print_xpm)(xpm_map_t xpm, uint16_t x, uint16_t y);
vbe_mode_info_t modeinfo;
uint8_t* frame_buffer;
unsigned buffer_index;
unsigned bytes_per_pixel;
unsigned frame_size;


#endif

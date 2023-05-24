#ifndef __GRAPHICS_H
#define __GRAPHICS_H

#include <lcom/lcf.h>
#include "VBE.h"

int (set_graphics_mode)(uint16_t mode);
int (set_frame_buffer)(uint16_t mode);


vbe_mode_info_t modeinfo;
uint8_t* frame_buffer;
#endif

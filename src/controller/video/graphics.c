#include <lcom/lcf.h>
#include "graphics.h"

int (set_graphics_mode)(uint16_t mode) {
  reg86_t reg86; // struct that supports instructions
  memset(&reg86, 0, sizeof(reg86)); // puts everything 0
  reg86.intno = 0x10; // it's always 0x10
  reg86.ah = 0x4F; // most significant part of AX
  reg86.al = 0x02; // least significant part of AX that is 0x02 in graphic mode
  reg86.bx = mode | BIT(14); // determines the mode with linear frame buffer
  if (sys_int86(&reg86) != OK) {
    printf("Error exiting graphics mode");
    return !OK;
  }
  return OK;
}

int (set_text_mode)() {
  reg86_t reg86;
  memset(&reg86 , 0, sizeof(reg86));
  reg86.intno = 0x10;
  reg86.ah = 0x00; 
  reg86.al = 0x03; // 0x03 is the text mode
  reg86.bx = 0x00; // there is no need to set the mode
  if (sys_int86(&reg86) != 0) {
    printf("Set text mode failed");
    return !OK;
  }
  return OK;
}

int (set_frame_buffer)(uint16_t mode) {
  
  memset(&modeinfo, 0, sizeof(modeinfo)); // puts everything 0
  if (vbe_get_mode_info(mode, &modeinfo) != OK) { // gets the mode info
    printf("Error getting mode info");
    return !OK;
  }

  // We have to calculate the size of the frame buffer
  bytes_per_pixel = (modeinfo.BitsPerPixel + 7) / 8; // adds 7 to the bits per pixel and divides by 8 because we want the number of bytes

  frame_size = modeinfo.XResolution * modeinfo.YResolution * bytes_per_pixel; // calculates the size of the frame buffer in bytes
  buffer_index = 0;
  // We have to map the frame buffer
  struct minix_mem_range physical_memory; // struct that supports memory ranges
  physical_memory.mr_base = modeinfo.PhysBasePtr; // the base address of the frame buffer
  physical_memory.mr_limit = physical_memory.mr_base + frame_size; // the limit address of the frame buffer

  // Allocates the memory range
  if (sys_privctl(SELF, SYS_PRIV_ADD_MEM, &physical_memory) != OK) {
    printf("Error allocating memory range");
    return !OK;
  }

  // virtual address of the frame buffer
  frame_buffer = vm_map_phys(SELF, (void*)physical_memory.mr_base, frame_size * 2);

  if (frame_buffer == NULL) {
    printf("Error mapping the frame buffer");
    return !OK;

  }
  return OK;
}

int (vg_draw_pixel)(uint16_t x, uint16_t y, uint32_t color) {
  if (x > modeinfo.XResolution || y > modeinfo.YResolution) {   //TODO limites
    printf("Error: pixel out of bounds");
    return !OK;
  }
  
  unsigned int index = (modeinfo.XResolution * y + x) * bytes_per_pixel; // calculates the index of the pixel
  if (buffer_index == 1)
    index += frame_size;

  if (memcpy(&frame_buffer[index], &color, bytes_per_pixel) == NULL) {
    printf("Error copying the pixel");
    return !OK;
  }
  return OK;
}

int (vg_draw_hline)(uint16_t x, uint16_t y, uint16_t len, uint32_t color) {
  for (unsigned i = 0; i < len; i++) {
    if (vg_draw_pixel(x + i, y, color) != OK) {
      printf("Error drawing the pixel");
      return !OK;
    }
  }
  return OK;
}

int (vg_draw_rectangle)(uint16_t x, uint16_t
 y, uint16_t width, uint16_t height, uint32_t color) {
  for (unsigned i = 0; i < height; i++) {
    if (vg_draw_hline(x, y + i, width, color) != OK) {
      printf("Error during rectangle drawing");
      vg_exit();
      return !OK;
    }
  }
  return OK;
 }

int (print_xpm)(xpm_map_t xpm, uint16_t x, uint16_t y) {
  xpm_image_t img;
  uint8_t * colors = xpm_load(xpm, XPM_INDEXED, &img);

  for (int h = 0; h < img.height; h++) {
    for (int w = 0; w < img.width; w++) {
      if (vg_draw_pixel(x + w, y + h, *colors) != OK) return !OK;
      colors++;
    }
  }
    printf("%d", buffer_index == 1);

  return OK;
}

void (clear_vram) () {
  vg_draw_rectangle(0,0, modeinfo.XResolution, modeinfo.YResolution, 0);
}

int (vg_set_start) () {
  reg86_t r86;

  memset(&r86, 0, sizeof(r86));

  r86.intno = 0x10;
  r86.ah = 0x4F;
  r86.al = 0x07;
  r86.bh = 0x00;
  r86.bl = 0x00;
  r86.cx = 0;
  r86.dx = modeinfo.YResolution * buffer_index;

  if (sys_int86(&r86) != OK) {
    printf("\tvg_exit(): sys_int86() failed \n");
    return 1;
  }
  buffer_index++;
  buffer_index = buffer_index % 2;
  return 0;
}

int (normalize_color)(uint32_t color, uint32_t *new_color) {
  if (modeinfo.BitsPerPixel == 32) *new_color = color;
  else *new_color = color & (BIT(modeinfo.BitsPerPixel) - 1);
  return OK;
}





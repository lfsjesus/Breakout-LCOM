#include "graphics.h"

int (set_graphics_mode)(uint16_t mode) {
  // create the struct that holds the config
  reg86_t reg86;
  // put everything to zero
  memset(&reg86, 0, sizeof(reg86));
  reg86.intno = 0x10;
  reg86.ah = 0x4F;
  reg86.al = 0x02;
  reg86.bx = mode | BIT(14); // determines mode with linear frame buffer

  // sys_int86 to write the config
  if (sys_int86(&reg86)) {
    printf("Could not set graphics mode");
    return !OK;
  }
  return OK;
}

int (set_frame_buffer)(uint16_t mode) {
  memset(&modeinfo, 0, sizeof(modeinfo));
  if (vbe_get_mode_info(mode, &modeinfo) != OK) {
    printf("Could not get mode info");
    return !OK;
  } 

  // how many bytes each pixel take
  unsigned int bytes_per_pixel = (modeinfo.BitsPerPixel + 7) / 8;

  unsigned int frame_size  = modeinfo.XResolution * modeinfo.YResolution * bytes_per_pixel;

  struct minix_mem_range physical_memory;
  physical_memory.mr_base = modeinfo.PhysBasePtr;
  physical_memory.mr_limit = physical_memory.mr_base + frame_size;

  // allocate the memory range suign sys_privctl
  if (sys_privctl(SELF, SYS_PRIV_ADD_MEM, &physical_memory) != OK) {
    printf("Could not allocate memory");
    return !OK;
  }

  // virtual address of frame buffer
  frame_buffer = vm_map_phys(SELF, (void*)physical_memory.mr_base, frame_size);

  if (frame_buffer == NULL) {
    printf("Could not map the frame buffer");
    return !OK;
  }

  return OK;
}

int (vg_draw_pixel)(uint16_t x, uint16_t y, uint32_t color) {
  if (x > modeinfo.XResolution || y > modeinfo.YResolution) {
    printf("Pixel out of bounds");
    return !OK;
  }

  unsigned bytes_per_pixel = (modeinfo.BitsPerPixel + 7 ) / 8;
  unsigned int index = (modeinfo.XResolution * y + x) * bytes_per_pixel;

  if (memcpy(&frame_buffer[index], &color, bytes_per_pixel) != OK) {
    printf("Could not copy the pixel");
    return !OK;
  }

  return OK;
}

int (vg_draw_hline)(uint16_t x, uint16_t y, uint16_t len, uint32_t color) {
  for (unsigned i = 0; i < len; i++) {
    if (vg_draw_pixel(x + i, y, color) != OK) {
      printf("Error drawing");
      return !OK;
    }
  }
  return OK;
}

int (vg_draw_rectangle)(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint32_t color) {
  for (unsigned i = 0; i < height; i++) {
    if (vg_draw_hline(x, y + 1, width, color) != OK) {
      printf("Could not draw rectangle");
      vg_exit();
      return !OK;
    }
  }
  return OK;
}

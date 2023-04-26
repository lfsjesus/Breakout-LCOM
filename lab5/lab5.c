// IMPORTANT: you must include the following line in all your C files
#include <lcom/lcf.h>

#include "graphics.h"
#include "keyboard.h"
#include "i8042.h"
#include <lcom/lab5.h>

#include <stdint.h>
#include <stdio.h>

// Any header files included below this line should have been created by you

int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need it]
  lcf_trace_calls("/home/lcom/labs/g4/lab5/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/g4/lab5/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}

int (wait_ESC_key)() {
  int ipc_status;
  int r;
  uint8_t bit_no;
  uint8_t irq_set;
  message msg;

  extern uint8_t scancode;
  
  if (keyboard_subscribe_int(&bit_no) != OK)
    return !OK;

  irq_set = BIT(bit_no);
  uint8_t bytes[2] = {0,0};
  int i = 0;

  while(scancode != ESC_BK_CODE) {
    if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
      printf("driver receive failed with: %d", r);
      continue;
    }
    if (is_ipc_notify(ipc_status)) {
      switch (_ENDPOINT_P(msg.m_source)) {
        case HARDWARE:
          if (msg.m_notify.interrupts & irq_set) {
            kbc_ih();
            bytes[i] = scancode;
            if ((scancode != TWO_BYTE) && (i == 0)) {
              kbd_print_scancode(!BREAK_CODE(scancode), 1, bytes);
            }
            else if ((scancode != TWO_BYTE)) {
              kbd_print_scancode(!BREAK_CODE(scancode), 2, bytes);
              i = 0;
            }
            else {
              i = 1;
            }
          }
          break;
        default:
          break;
      }
    }
  }

  if (keyboard_unsubscribe_int() != OK) {
    return !OK;
  }

  return OK;
}

int(video_test_init)(uint16_t mode, uint8_t delay) {
  if (set_graphics_mode(mode) != OK) {
    printf("Error setting graphics mode");
    return !OK;
  }

  sleep(delay);

  if (vg_exit() != OK) {
    printf("Error setting text mode");
    return !OK;
  }

  return OK;
}

int(video_test_rectangle)(uint16_t mode, uint16_t x,  uint16_t y,
                          uint16_t width, uint16_t height, uint32_t color) {
  
  // build the frame buffer
  if (set_frame_buffer(mode) != OK) return !OK;
  
  // change to graphic mode
  if (set_graphics_mode(mode) != OK) return !OK;

  // normalize colors
  uint32_t new_color;
  if (normalize_color(color, &new_color) != OK) return !OK;

  if (vg_draw_rectangle(x, y, width, height, new_color) != OK) return !OK;

  if (wait_ESC_key() != OK) return !OK;

  if (vg_exit() != OK) return !OK;

  return OK;
}

int(video_test_pattern)(uint16_t mode, uint8_t no_rectangles, uint32_t first, uint8_t step) {
  if (set_frame_buffer(mode) != OK) return !OK;

  if (set_graphics_mode(mode) != OK) return !OK;

  int vertical = modeinfo.YResolution / no_rectangles;
  int horizontal = modeinfo.XResolution / no_rectangles;

  for (int i = 0; i < no_rectangles; i++) {
    for (int j = 0; j < no_rectangles; j++) {
      uint32_t color;

      if (modeinfo.MemoryModel == DIRECT_COLOR) {
        uint32_t r = Red(j, step, first);
        uint32_t g = Green(i, step, first);
        uint32_t b = Blue(j, i, step, first);
        color = direct_mode(r,g,b);
      }
      else {
        color = indexed_mode(j, i, step, first, no_rectangles);
      }

      if (vg_draw_rectangle(j * horizontal, i * vertical, horizontal, vertical, color)) {
        return !OK;
      }
    }
  }

  if (wait_ESC_key()) return !OK;

  if (vg_exit()) return !OK;

  return OK;
}

int(video_test_xpm)(xpm_map_t xpm, uint16_t x, uint16_t y) {
  if (set_frame_buffer(VBE_768p_INDEX)) return !OK;

  if (set_graphics_mode(VBE_768p_INDEX)) return !OK;

  if (print_xpm(xpm, x, y) != 0) return !OK;

  if (wait_ESC_key() != OK) return !OK;

  return vg_exit();
}

int(video_test_move)(xpm_map_t xpm, uint16_t xi, uint16_t yi, uint16_t xf, uint16_t yf,
                     int16_t speed, uint8_t fr_rate) {
  
  int ipc_status;
  int r;
  uint8_t bit_no_timer;
  uint8_t bit_no_kbd;
  uint8_t irq_set_timer;
  uint8_t irq_set_kbd;
  message msg;
  extern uint8_t scancode;
  extern uint32_t counter;
  if (keyboard_subscribe_int(&bit_no_kbd) != OK) return !OK;

  if (timer_subscribe_int(&bit_no_timer) != OK) return !OK;

  if (timer_set_frequency(0, fr_rate) != OK) return !OK;

  if (set_frame_buffer(VBE_768p_INDEX) != OK) return !OK;

  if (set_graphics_mode(VBE_768p_INDEX) != OK) return !OK;

  if (print_xpm(xpm, xi, yi) != OK) return !OK;

  irq_set_timer = BIT(bit_no_timer);
  irq_set_kbd = BIT(bit_no_kbd);

  bool vertical = (xi == xf) ? true : false;

  while (scancode != ESC_BK_CODE) {
    if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
      printf("driver receive failed with: %d", r);
      continue;
    }

    if (is_ipc_notify(ipc_status)) {
      switch (_ENDPOINT_P(msg.m_source)) {
        case HARDWARE:
          if (msg.m_notify.interrupts & irq_set_kbd) {
            kbc_ih();
          }

          if (msg.m_notify.interrupts & irq_set_timer) {
            timer_int_handler();
            if (vg_draw_rectangle(xi, yi, 100, 100, 0x000000) != OK) return !OK;
            if (speed > 0) {
              if (vertical) {
                if (yi < yf) {
                  if (speed > 0) {
                    if (yi + speed > yf) yi = yf;
                    else yi += speed;
                  }
                  else {
                    if (yi + speed < yf) yi = yf;
                    else yi += speed;
                  }
                }
                else {
                  if (speed > 0) {
                    if (yi - speed < yf) yi = yf;
                    else yi -= speed;
                  }
                  else {
                    if (yi - speed > yf) yi = yf;
                    else yi -= speed;
                  }
                }
              }
              else {
                if (xi < xf) {
                  if (xi + speed > xf) xi = xf;
                  else xi += speed;
                }
                else {
                  if (xi - speed < xf) xi = xf;
                  else xi -= speed;
                }
              }
            }
            else {
              if (counter % (-speed) == 0) {
                if (vertical) {
                  if (yi < yf) yi++;
                  else yi = yf;
                }
                else {
                  if (xi < xf) xi++;
                  else xi = xf;
                }
              }
            }

            if (print_xpm(xpm, xi, yi) != OK) return !OK;
          }
          break;
        default:
          break;
        }
        
      }
    }
  
  if (vg_exit() != OK) return !OK;
  if (timer_unsubscribe_int() != OK) return !OK;
  if (keyboard_unsubscribe_int() != OK) return !OK; 

  return OK;
}

int(video_test_controller)() {
  /* To be completed */
  printf("%s(): under construction\n", __func__);

  return 1;
}

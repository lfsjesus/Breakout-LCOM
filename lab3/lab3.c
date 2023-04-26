#include <lcom/lcf.h>

#include <lcom/lab3.h>

#include <stdbool.h>
#include <stdint.h>
#include "keyboard.h"
#include "i8042.h"
#include "i8254.h"

int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need it]
  lcf_trace_calls("/home/lcom/labs/g4/lab3_rewrite/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/g4/lab3_rewrite/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}

int(kbd_test_scan)() {
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

int(kbd_test_poll)() {
  uint8_t scancode = 0;
  uint8_t bytes[2] = {0};
  int i = 0;

  while (scancode != ESC_BK_CODE) {
    if (read_output_buffer(&scancode) != OK) continue;
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

  if (keyboard_restore() != OK) {
    printf("ERROR\n");
  }

  return OK;  
}


int(kbd_test_timed_scan)(uint8_t n) {
  int ipc_status;
  int r;
  uint8_t bit_no_kbd;
  uint8_t bit_no_timer;
  uint8_t irq_set_kbd;
  uint8_t irq_set_timer;
  message msg;

  uint8_t bytes[2] = {0,0};
  int i = 0;
  extern uint32_t counter;
  extern uint8_t scancode;
  int seconds = 0;

  if (keyboard_subscribe_int(&bit_no_kbd) != OK)
    return !OK;

  if (timer_subscribe_int(&bit_no_timer) != OK)
    return !OK;

  irq_set_kbd = BIT(bit_no_kbd);
  irq_set_timer = BIT(bit_no_timer);

  while((scancode != ESC_BK_CODE) && (seconds < n)) {
    if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
      printf("driver receive failed with: %d", r);
      continue;
    }
    if (is_ipc_notify(ipc_status)) {
      switch (_ENDPOINT_P(msg.m_source)) {
        case HARDWARE:
          if (msg.m_notify.interrupts & irq_set_kbd) {
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
            counter = 0;
            seconds = 0;

          }
          if (msg.m_notify.interrupts & irq_set_timer) {
            timer_int_handler();
            // if n seconds have passed since last key press
            if (counter % 60 == 0) {seconds++;}
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

  if (timer_unsubscribe_int() != OK) {
    return !OK;
  }

  return OK;
}


#include <lcom/lcf.h>

#include <lcom/lab3.h>

#include <stdbool.h>
#include <stdint.h>
#include "keyboard.h"
#include "i8042.h"
#include "i8254.h"

extern int sys_inb_count;
extern uint32_t counter;

int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need it]
  lcf_trace_calls("/home/lcom/labs/lab3/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/lab3/output.txt");

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
  message msg;
  uint8_t bit_no;

  if (kbd_subscribe_int(&bit_no) != OK) {
    perror("Error subscribing keyboard interrupts\n");
    return !OK;
  }

  int r;
  uint8_t irq_set = BIT(bit_no);

  int index = 0;
  int esc = 0;
  // Loop while the ESC key is not pressed
  while (!esc) {
    if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
      printf("driver_receive failed with: %d", r);
      continue;
    }

    if (is_ipc_notify(ipc_status)) {
      switch (_ENDPOINT_P(msg.m_source)) {
        case HARDWARE:
          if (msg.m_notify.interrupts & irq_set) {
            kbc_ih();
            uint8_t* scancode = get_scancode();

            if(scancode[index] == ESC_BK_CODE) {
              esc = 1;
            }

            if (scancode[index] == TWO_BYTE_CODE) {
              index = 1;
              continue;
            }
            
            kbd_print_scancode(!BREAK_CODE(scancode[index]), index + 1, scancode);
            index = 0;

          }
          break;

        default:
          break;
      }
    }
  }

  if (kbd_unsubscribe_int() != OK) {
    perror("Error unsubscribing keyboard interrupts\n");
    return !OK;
  }


  kbd_print_no_sysinb(sys_inb_count);
  return OK;
}

int(kbd_test_poll)() {
  uint8_t status;
  int index = 0;
  int esc = 0;

  uint8_t restore = kbd_dis_int(&restore);

  while (!esc) {
    if (kbd_read_status(&status) != OK) {
      perror("Error reading status register\n");
      return !OK;
    }

    if (kbc_read_byte() != OK) {
      micro_delay(5000);
      continue;
    }

    uint8_t* scancode = get_scancode();

    if(scancode[index] == ESC_BK_CODE) {
      esc = 1;
    }

    if (scancode[index] == TWO_BYTE_CODE) {
      index = 1;
      continue;
    }

    kbd_print_scancode(!BREAK_CODE(scancode[index]), index + 1, scancode);
    index = 0;

  }

  if (sys_outb(STAT_REG, restore) != OK) {
    perror("Error reenabling interrupts\n");
    return !OK;
  }
  
  kbd_print_no_sysinb(sys_inb_count);
  return OK;
}


int(kbd_test_timed_scan)(uint8_t n) {
  int ipc_status;
  int r;
  message msg;
  int index = 0;
  int esc = 0;

  uint8_t kbd_bit_no;
  uint8_t timer_bit_no;

  if (kbd_subscribe_int(&kbd_bit_no) != OK) {
    perror("Error subscribing keyboard interrupts\n");
    return !OK;
  }

  if (timer_subscribe_int(&timer_bit_no) != OK) {
    perror("Error subscribing timer interrupts\n");
    return !OK;
  }

  uint8_t irq_set_kbd = BIT(kbd_bit_no);
  uint8_t irq_set_timer = BIT(timer_bit_no);

  while (!esc) {
    if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
      printf("driver_receive failed with: %d", r);
      continue;
    }

    if (is_ipc_notify(ipc_status)) {
      switch (_ENDPOINT_P(msg.m_source)) {
        case HARDWARE:
          if (msg.m_notify.interrupts & irq_set_kbd) {
            kbc_ih();
            uint8_t* scancode = get_scancode();

            if (scancode[index] == ESC_BK_CODE) {
              esc = 1;
            }

            if (scancode[index] == TWO_BYTE_CODE) {
              index = 1;
              continue;
            }

            kbd_print_scancode(!BREAK_CODE(scancode[index]), index + 1, scancode);

            index = 0;
          }

          if (msg.m_notify.interrupts & irq_set_timer) {
            timer_int_handler();
            if (counter/60 >= n) break;
          }
      break;

        default:
          break;
      }
    }
  }

  if (kbd_unsubscribe_int() != OK) {
    perror("Error unsubscribing keyboard interrupts\n");
    return !OK;
  }

  if (timer_unsubscribe_int() != OK) {
    perror("Error unsubscribing timer interrupts\n");
    return !OK;
  }

  return OK;
}


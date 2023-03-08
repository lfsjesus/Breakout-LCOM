#include <lcom/lcf.h>
#include "keyboard.h"
#include "i8042.h"

static int hook_id = KBD_IRQ;
static uint8_t scancode[2] = {0}; // Array to store the scancodes
static int sc_index = 0; // Index to scancode array

uint8_t* get_scancode() {
  return scancode;
}

int (kbd_subscribe_int)(uint8_t *bit_no) {
  *bit_no = hook_id;
  return sys_irqsetpolicy(KBD_IRQ, IRQ_REENABLE | IRQ_EXCLUSIVE, &hook_id);
}

int (kbd_unsubscribe_int)() {
  return sys_irqrmpolicy(&hook_id);
} 

int (kbd_read_status)(uint8_t *status) {
  if (util_sys_inb(STAT_REG, status) != OK) {
    return !OK;
  }
  return OK;
}

int (kbc_read_byte)() {
  uint8_t status;

  if (kbd_read_status(&status) != OK) {
    perror("Error reading status register\n");
    return !OK;
  }

  if (status & (PAR_ERR | TO_ERR)) {
    perror("Parity/Timeout error\n");
    return !OK;
  }

  if (status & AUX) {
    perror("Mouse data\n");
    return !OK;
  }

  if (status & OUT_BUF_FULL) {
    uint8_t byte;

    if (util_sys_inb(OUT_BUF, &byte) != OK) {
      return !OK;
    }
    
    scancode[sc_index] = byte;

    if (scancode[sc_index] == TWO_BYTE_CODE) {
      sc_index = 1;
    }
    else {
      sc_index = 0;
    }   
  }  

  return OK;
}

void (kbc_ih)() {
  kbc_read_byte();
}



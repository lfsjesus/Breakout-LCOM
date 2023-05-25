#include <lcom/lcf.h>
#include "serialport.h"
static int sp_hook_id = COM1_IRQ;

int (sp_subscribe_int) (uint8_t *bit_no) {
  (*bit_no) = sp_hook_id;
  return sys_irqsetpolicy(KEYBOARD_IRQ, IRQ_REENABLE | IRQ_EXCLUSIVE, &sp_hook_id);
}
int (sp_unsubscribe_int) () {
  return sys_irqrmpolicy(&sp_hook_id);
}


void (sp_ih)() {
  Queue queue;
  uint8_t iir, lsr, c;
  if (utils_sys_inb(COM1_ADDR + IIR, &iir)!= 0) //  read IIR
    return 1;
  if (utils_sys_inb(COM1_ADDR + LSR, &lsr) != 0)  // read LSR again
    return 1;

  while (!isFull(&queue) && (lsr & LSR_ReceiverData)) {
    if (sys_inb(COM1_ADDR + RBR, &c) != 0) return 1;    // read char
    push(&queue, c);                                      // push char into queue -> handled later
    if (utils_sys_inb(COM1_ADDR + LSR, &lsr) != 0) return 1;   // read LSR again
  }

  
}



int (enable_fifo) () {
  uint8_t command = FCR_EB;
  return sys_outb(COM1_ADDR + FCR, command);
}

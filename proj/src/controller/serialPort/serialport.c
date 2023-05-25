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
    return;
  // RECEBER char e mandar para a receiving queue (fazer função à parte)
  /*if (read_lsr(&lsr) != 0)  return 1; 
  while (!isFull(&queue) && (lsr & LSR_ReceiverData)) {
    if (sys_inb(COM1_ADDR + RBR, &c) != 0) return 1;      // read char
    push(&queue, c);                                      // push char into queue -> handled later
    if (read_lsr != 0) return 1;   // read LSR again
  }*/

  if(!(iir & IIR_INT)) {    //  Não tenho a certeza à cerca da negação
      /*switch( iir & INT_ID ) {
      case SER_RX_INT:
      ... // read received character
      case SER_TX_INT:
      ... // put character to sent 
      case SER_RX_ERR:
      ... // notify upper level 
      case SER_XXXX:
      ... // depends on XXX 
      }*/
      }

}

int (read_lsr) (uint8_t* lsr) {
    if (utils_sys_inb(COM1_ADDR + LSR, &lsr) != 0)  
      return 1;
    if (*lsr & (LSR_FE | LSR_OE | LSR_PE)) {
      printf("LSR error\n");
      return 1;
    }
    return 0;
}

int (send_byte) (uint8_t* byte) {

}

int (read_byte) () {

}

int (enable_fifo) () {
  uint8_t command = FCR_EB;
  return sys_outb(COM1_ADDR + FCR, command);
}



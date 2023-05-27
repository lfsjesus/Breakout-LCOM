#include <lcom/lcf.h>
#include "serialport.h"

static int sp_hook_id = COM1_IRQ;
static Queue* queue;

int (sp_subscribe_int) (uint8_t *bit_no) {
  (*bit_no) = sp_hook_id;
  return sys_irqsetpolicy(COM1_IRQ, IRQ_REENABLE | IRQ_EXCLUSIVE, &sp_hook_id);
}
int (sp_unsubscribe_int) () {
  return sys_irqrmpolicy(&sp_hook_id);
}

int (sp_setup) () {
  queue = createQueue(100);
  uint8_t ier;
  if (util_sys_inb(COM1_ADDR + IER, &ier) != 0) return 1;  //Ler IER
  ier &= 0xF0;                                // Limpar as configurações
  ier |= IER_RDA;                             // Inicializar IER com Read DataAvailable
  if (sys_outb(COM1_ADDR + IER, (uint32_t)ier) != 0) return 1; //Escrever IER
  return 0;
  }

void (sp_ih)() {
  uint8_t iir, lsr;
  if (util_sys_inb(COM1_ADDR + IIR, &iir)!= 0) //  read IIR
    return;


  if(!(iir & IIR_INT)) {    // Se houver interrupção
      if(iir & IIR_INT_ID == IIR_PRIO_CTO) {  // FIFO charcter Timeout
        if (read_lsr(&lsr) != 0)  return; 
        while (!isFull(queue) && (lsr & LSR_ReceiverData)) {
          read_byte();
          if (read_lsr(&lsr)!= 0) return;
      }
    }
  }
}

int (read_lsr) (uint8_t* lsr) {
    if (util_sys_inb(COM1_ADDR + LSR, lsr) != 0)  
      return 1;
    if (*lsr & (LSR_FE | LSR_OE | LSR_PE)) {
      printf("LSR error\n");
      return 1;
    }
    return 0;
}

int (send_byte) (uint8_t* byte) {
  uint8_t lsr;
  if (util_sys_inb(COM1_ADDR + LSR, &lsr) != 0)  return 1;
  if (lsr & LSR_THRempty) {
    if (sys_outb(COM1_ADDR + THR, (uint32_t)byte) == 0) {return 0;}
  }
  printf("error");
  return 1;
}

int (read_byte) () {
  uint8_t c, lsr;
  if (read_lsr(&lsr) != 0)  return 1;
  if (util_sys_inb(COM1_ADDR + RBR, &c) != 0)
    return 1;
  push(queue, c);

  return 0;
}

Queue* get_queue () {
  return queue;
}



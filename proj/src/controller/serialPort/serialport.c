#include <lcom/lcf.h>
#include "serialport.h"

static int sp_hook_id = COM1_IRQ;
static Queue* queue;

static uint8_t mouse_packet[4];
extern MouseInfo guest_mouse_info;



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
    printf("INTERRUPT!!!!\n");
      if(iir & IIR_INT_ID == IIR_PRIO_CTO) {  // FIFO charcter Timeout
        printf("CTO\n");
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

int (send_byte) (uint8_t byte) {
  uint8_t lsr, attempts = 10;
  while (attempts > 0) {

    if (util_sys_inb(COM1_ADDR + LSR, &lsr) != 0)  return 1;
    if (lsr & LSR_THRempty) {
      if (sys_outb(COM1_ADDR + THR, byte) == 0) {return 0;}
    }
    attempts--;
  }
  printf("sending byte error\n");
  return 1;
}

int (read_byte) () {
  uint8_t c, lsr;
  if (read_lsr(&lsr) != 0)  return 1;
  if (util_sys_inb(COM1_ADDR + RBR, &c) != 0)
    return 1;
  printf("push%d\n", c);
  push(queue, c);

  return 0;
}

int (sp_read_playing_byte) (uint8_t byte) {
  printf("reading playing byte\n");
  if (byte == GAMEOVER_BYTE) 
    //change gameState and return
    return 0;
    
  if (byte == PACKET_BYTE) {
    sp_read_packet();
  }
  return 0;
}

int (sp_read_packet) () {
  printf("reading packet\n");
    int n_bytes = 0;
    uint8_t byte;
    while (n_bytes < 4) {
      sp_ih();
      byte = pop(get_queue());  //posso alterar o arg?
      mouse_packet[n_bytes] = byte;
      n_bytes++;
    }
    sp_parse_mouse_packet();
    return 0;
}


int (sp_parse_mouse_packet) () {
  uint16_t x = (((uint16_t) mouse_packet[0]) << 8) | ((uint16_t) mouse_packet[1]);
  uint16_t y = (((uint16_t) mouse_packet[2]) << 8) | ((uint16_t) mouse_packet[3]);
  guest_mouse_info.x = x;
  guest_mouse_info.y = y;
  return 0;
}

int (send_mouse_packet) (MouseInfo mouse_info) {
  if (send_byte(PACKET_BYTE) != 0)  { return 1;}
  uint8_t xMSB,xLSB, yMSB, yLSB;
  util_get_LSB(mouse_info.x, &xLSB);
  util_get_MSB(mouse_info.x, &xMSB);
  util_get_LSB(mouse_info.y, &yLSB);
  util_get_MSB(mouse_info.y, &yMSB);
  if (send_byte(xMSB) != 0) { return 1;}
  if (send_byte(xLSB) != 0) { return 1;}
  if (send_byte(yMSB) != 0) { return 1;}
  if (send_byte(yLSB) != 0) { return 1;}

  return 0;
}


Queue* get_queue () {
  return queue;
}



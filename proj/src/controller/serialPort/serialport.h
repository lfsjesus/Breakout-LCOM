#ifndef __SERIAL_PORT_H
#define __SERIAL_PORT_H

#include "queue.h"
#include "uart.h"

int (sp_subscribe_int) (uint8_t *bit_no);
int (sp_unsubscribe_int) ();
void (sp_ih)();

int (read_iir) (uint8_t* status);
int (enable_fifo) ();
#endif

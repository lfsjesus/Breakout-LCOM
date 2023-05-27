#ifndef __SERIAL_PORT_H
#define __SERIAL_PORT_H

#include "queue.h"
#include "uart.h"
#include "util.h"
#include "../keyboard_mouse/mouse.h"

int (sp_subscribe_int) (uint8_t *bit_no);
int (sp_unsubscribe_int) ();
void (sp_ih)();

int (sp_setup)();
int (read_lsr) (uint8_t* status);
int (send_byte) (uint8_t* byte);
int (read_byte) ();
int (sp_playing_byte) (uint8_t byte);
int (sp_parse_mouse_packet) ();

Queue* get_queue();
#endif

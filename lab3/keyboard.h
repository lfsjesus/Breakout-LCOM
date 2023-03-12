#ifndef _LCOM_KEYBOARD_H_
#define _LCOM_KEYBOARD_H_

#include <lcom/lcf.h>
#include <minix/sysutil.h>

int (kbd_subscribe_int)(uint8_t *bit_no);
int (kbd_unsubscribe_int)();
int (kbd_read_status)(uint8_t *status);
int (kbc_read_byte)();
uint8_t* (get_scancode)();
int (kbd_dis_int)(uint8_t* restore);

#endif /* _LCOM_KEYBOARD_H_ */

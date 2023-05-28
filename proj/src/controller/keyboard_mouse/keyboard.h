#ifndef _MOUSE_LCOM_
#define _MOUSE_LCOM_

#include <lcom/lcf.h>

int (keyboard_subscribe_int)();
int (keyboard_unsubscribe_int)();
void (kbc_ih)();
int (keyboard_restore)();

#endif

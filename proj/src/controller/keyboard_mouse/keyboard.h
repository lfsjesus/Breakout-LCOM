#ifndef _MOUSE_LCOM_
#define _MOUSE_LCOM_

#include <lcom/lcf.h>

<<<<<<< HEAD
int (keyboard_subscribe_int)();
=======
/**
 * @brief Subscribes keyboard interrupts
 * @param bit_no
 * @return int - 0 on success, 1 on failure
 */
int (keyboard_subscribe_int)(uint8_t *bit_no);
/**
 * @brief Unsubscribes keyboard interrupts
 * @return int - 0 on success, 1 on failure
 */
>>>>>>> documentation
int (keyboard_unsubscribe_int)();
/**
 * @brief Reads the output buffer
 */
void (kbc_ih)();
/**
 * @brief Restores the keyboard
 * @return int - 0 on success, 1 on failure
 */
int (keyboard_restore)();

#endif

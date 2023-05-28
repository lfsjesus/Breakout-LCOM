#ifndef _MOUSE_LCOM_
#define _MOUSE_LCOM_

#include <lcom/lcf.h>

/**
 * @brief Subscribes keyboard interrupts
 * @param bit_no
 * @return int - 0 on success, 1 on failure
 */
int (keyboard_subscribe_int)();

/**
 * @brief Unsubscribes keyboard interrupts
 * @return int - 0 on success, 1 on failure
 */
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

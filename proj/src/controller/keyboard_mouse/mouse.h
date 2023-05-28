#ifndef __MOUSE
#define __MOUSE

#include <minix/sysutil.h>
#include "i8042.h"
#include <lcom/lcf.h>
#include <stdint.h>
#include <stdio.h>
#include "../video/graphics.h"

/**
 * @brief configures the mouse
 * @param control_word
 * @return int - 0 on success and 1 on failure
 */
int (mouse_config)(uint8_t control_word);
/**
 * @brief Subscribes mouse interrupts
 * @return int - 0 on success and 1 on failure
 */
int (mouse_subscribe_int)(uint8_t *bit_no);
/**
 * @brief When interrupt handler is called, reads a new byte from the mouse
 */
void (mouse_ih)();
/**
 * @brief Unsubscribes mouse interrupts
 * @return int - 0 on success and 1 on failure
 */
int (mouse_unsubscribe_int)();
/**
 * @brief Evaluates the mouse_bytes array and acts accordingly
 * @return int - 0 on success and 1 on failure
 */
int (mouse_sync)();
/**
 * @brief Processes the mouse packet
 * @return int - 0 on success and 1 on failure
 */
int (mouse_process_packet)();
/**
 * @brief Syncronizes the information from the mouse
 * @return int - 0 on success and 1 on failure
 */
void (sync_mouse_info) ();

/**
 * @brief Struct to store information from the mouse
 */
typedef struct {
    uint8_t right_click;
    uint8_t left_click;
    int16_t x;
    int16_t y;
} MouseInfo;   


#endif

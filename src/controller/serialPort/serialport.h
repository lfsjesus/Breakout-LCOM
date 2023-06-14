#ifndef __SERIAL_PORT_H
#define __SERIAL_PORT_H

#include "queue.h"
#include "uart.h"
#include "util.h"
#include "../keyboard_mouse/mouse.h"
/**
 * @brief Subscribes Serial Port interrupts
 * @param bit_no
 * @return int - 0 on success, 1 on failure
*/
int (sp_subscribe_int) (uint8_t *bit_no);

/**
 * @brief Unsubscribes Serial Port interrupts
*/
int (sp_unsubscribe_int) ();
/**
 * @brief reads a byte from the RBR register
*/
void (sp_ih)();

/**
 * @brief enables serial port interrupts on Received Data Available and initializes the receiving queue
 * 
 * @return int - 0 on success, 1 on failure
*/
int (sp_setup)();

/**
 * @brief reads the Line Status Register
 * @return int - 0 on success, 1 on failure
*/
int (read_lsr) (uint8_t* status);

/**
 * @param byte to be sent
 * @brief writes byte to THR register
 * @return int - 0 on success, 1 on failure
*/
int (send_byte) (uint8_t byte);

/**
 * @brief reads byte from RBR register
 * @return int - 0 on success, 1 on failure
*/
int (read_byte) ();

/**
 * @brief clears both Receiving and Transmiting FIFO
 * @return int - 0 on success, 1 on failure
*/
int(sp_clear_queues) ();

/**
 * @param byte read
 * @brief processes the byte read accordingly during multiplayer game
 * @return int - 0 on success, 1 on failure
*/

int (sp_read_playing_byte) (uint8_t byte);

/**
 * @brief reads a full mouse packet
 * @return int - 0 on success, 1 on failure
*/
int (sp_read_packet) ();

/**
 * @brief parses the mouse_packet read into a struct
 * @return int - 0 on success, 1 on failure
*/
int (sp_parse_mouse_packet) ();

/**
 * @param information to be sent
 * @brief writes a mouse_packet to the THR register
 * @return int - 0 on success, 1 on failure
*/

int (send_mouse_packet) (MouseInfo mouse_info);

/**
 * @brief returns the receiving queue
 * @return receiving queue
*/

Queue* get_queue();
#endif

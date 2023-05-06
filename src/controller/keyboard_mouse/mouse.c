#include "mouse.h"

static int hook_id = MOUSE_IRQ;
uint8_t byte;
uint8_t mouse_bytes[3];
struct packet mouse_packet;
unsigned int packet_counter = 0;
MouseInfo mouse_info = {0, 0, 10, 10};
extern vbe_mode_info_t modeinfo;

int (mouse_config)(uint8_t control_word) {
  uint8_t response;

  do {

    if (write_kbc_command(STAT_REG, WRITE_BYTE_MOUSE)) return !OK;

    if (write_kbc_command(IN_OUT_BUF, control_word)) return !OK;

    tickdelay(micros_to_ticks(20000));

    if (util_sys_inb(IN_OUT_BUF, &response)) return !OK;

  } while (response != ACK);

  return OK;
}

int (mouse_subscribe_int)(uint8_t *bit_no) {
  (*bit_no) = hook_id;
  return sys_irqsetpolicy(MOUSE_IRQ, IRQ_REENABLE | IRQ_EXCLUSIVE, &hook_id);
}

int (mouse_unsubscribe_int)() {
  if (sys_irqrmpolicy(&hook_id)) return !OK;
  return OK;
}

void (mouse_ih)() {
  if (read_output(KBC_WRITE_CMD, &byte, 1)) {
    printf("Error: could not handle mouse interrupt");
  }
}

int (mouse_sync)() {
  if (packet_counter == 0 && (byte & FIRST_BYTE)) mouse_bytes[0] = byte;

  else mouse_bytes[packet_counter] = byte;
  
  packet_counter++;
  return OK;
}

int (mouse_process_packet)() {
  for (int i = 0; i < 3; i++) {
      mouse_packet.bytes[i] = mouse_bytes[i];
  }

  mouse_packet.lb = mouse_bytes[0] & MOUSE_LB;
  mouse_packet.mb = mouse_bytes[0] & MOUSE_MB;
  mouse_packet.rb = mouse_bytes[0] & MOUSE_RB;
  mouse_packet.x_ov = mouse_bytes[0] & MOUSE_X_OVERFLOW;
  mouse_packet.y_ov = mouse_bytes[0] & MOUSE_Y_OVERFLOW;
  mouse_packet.delta_x = (mouse_bytes[0] & MOUSE_X_SIGNAL) ? (0xff00 | mouse_bytes[1]) : mouse_bytes[1];
  mouse_packet.delta_y = (mouse_bytes[0] & MOUSE_Y_SIGNAL) ? (0xff00 | mouse_bytes[2]) : mouse_bytes[2];


  return OK;
}

void (sync_mouse_info) () {

  mouse_info.left_click = mouse_packet.lb;
  mouse_info.right_click = mouse_packet.rb;

  if (mouse_bytes[0] & MOUSE_X_OVERFLOW || mouse_bytes[0] & MOUSE_Y_OVERFLOW) return;

  if (mouse_packet.delta_x < 0 || mouse_packet.delta_x > modeinfo.XResolution || mouse_packet.delta_y < 0 || mouse_packet.delta_y > modeinfo.YResolution) return;

  mouse_info.x = mouse_packet.delta_x;
  mouse_info.y = mouse_packet.delta_y;
}


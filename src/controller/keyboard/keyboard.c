#include "keyboard.h"
#include "i8042.h"

static int hook_id = KEYBOARD_IRQ;
uint8_t scancode = 0;

int (keyboard_subscribe_int)(uint8_t *bit_no) {
  (*bit_no) = hook_id;
  return sys_irqsetpolicy(KEYBOARD_IRQ, IRQ_REENABLE | IRQ_EXCLUSIVE, &hook_id);
}

int (keyboard_unsubscribe_int)() {
  return sys_irqrmpolicy(&hook_id);
}

void (kbc_ih)() {
  if (read_output_buffer(&scancode) != OK)
    printf("Could not read Output Buffer\n");
}

int (keyboard_restore)() {
  uint8_t commandByte;
  if (write_kbc_command(STAT_REG, KBC_READ_CMD) != OK) {
    printf("Could not send read command\n");
    return !OK;
  }
  if (read_output_buffer(&commandByte) != OK) {
    printf("Could not read output buffer\n");
    return !OK;
  }
  
  commandByte |= KBD_ENABLE_INT;

  if (write_kbc_command(STAT_REG, KBC_WRITE_CMD) != OK) {
    printf("Could not write write command \n");
    return !OK;
  }
  
  if (write_kbc_command(IN_OUT_BUF, commandByte) != OK) {
    printf("Could not write commandbyte\n");
    return !OK;
  }
  
  return OK;
}

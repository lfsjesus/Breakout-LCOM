#include "i8042.h"
#include <lcom/lcf.h>

int read_status_register(uint8_t* status) {
  if (util_sys_inb(STAT_REG , status) != OK)
    return !OK;
  return OK;
}

int read_output(uint8_t port, uint8_t* byte, uint8_t mouse) {
  uint8_t status;
  uint8_t attempts = 3;

  while (attempts > 0) {
    if (read_status_register(&status) != OK) {
      printf("Could not read status register!\n");
      return !OK;
    }

    if ((status & OBF) != 0) {
      if (util_sys_inb(port, byte) != OK) {
        return !OK;
      }

      if ((status & PAR_ERR) != 0) {
        printf("Parity Error! \n");
        return !OK;
      }

      if ((status & TIMEOUT) != 0) {
        printf("Timeout error!\n");
        return !OK;
      }

      if (!mouse && (status & BIT(5))) {
        printf("Error: Keyboard output expected\n");
        return !OK;
      }

      if (mouse && !(status & BIT(5))) {
        printf("Error: Mouse output expected\n");
        return !OK;
      }

      return OK;
    }
    tickdelay(micros_to_ticks(40000));
    attempts--;
  }
  return !OK;
}

int write_kbc_command(uint8_t port, uint8_t commandByte) {
  uint8_t status;
  uint8_t attempts = 3;

  while (attempts > 0) {
    if (read_status_register(&status) != OK) {
      printf("Could not read output buffer!\n");
      return !OK;
    }

    if ((status & IBF) == 0) {
      if (sys_outb(port, commandByte) != OK) {
        printf("Could not write command!\n");
        return !OK;
      }
      return OK;
    }
    tickdelay(micros_to_ticks(20000));
    attempts--;
  }
  return !OK;
}

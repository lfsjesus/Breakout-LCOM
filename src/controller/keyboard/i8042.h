#include <lcom/lab3.h>

#define KEYBOARD_IRQ 1

#define PAR_ERR BIT(7)
#define TIMEOUT BIT(6)
#define IBF BIT(1)
#define OBF BIT(0)
#define IN_OUT_BUF 0x60
#define STAT_REG 0x64

#define ESC_MK_CODE 0x01
#define ESC_BK_CODE 0x81s

#define KBC_READ_CMD 0x20
#define KBC_WRITE_CMD 0x60

#define KBD_ENABLE_INT BIT(0)

#define BREAK_CODE(code) (BIT(7) & code)
#define TWO_BYTE 0xE0

/* FUNCTIONS */
int read_status_register(uint8_t* status);
int read_output_buffer(uint8_t* byte);
int write_kbc_command(uint8_t port, uint8_t commandByte);


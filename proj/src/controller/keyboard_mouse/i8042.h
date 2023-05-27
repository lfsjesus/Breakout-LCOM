#include <lcom/lab3.h>

#define KEYBOARD_IRQ 1
#define MOUSE_IRQ 12

#define PAR_ERR BIT(7)
#define TIMEOUT BIT(6)
#define IBF BIT(1)
#define OBF BIT(0)
#define IN_OUT_BUF 0x60
#define STAT_REG 0x64

#define ESC_MK_CODE 0x01
#define ESC_BK_CODE 0x81

#define S_MK_CODE 0x1F
#define S_BK_CODE 0x9F

#define P_MK_CODE 0x19
#define P_BK_CODE 0x99

#define H_MK_CODE 0x23
#define H_BK_CODE 0xA3

#define A_MK_CODE 0x1E
#define A_BK_CODE 0x9E

#define D_MK_CODE 0x20
#define D_BK_CODE 0xA0

#define KBC_READ_CMD 0x20
#define KBC_WRITE_CMD 0x60

#define KBD_ENABLE_INT BIT(0)

#define BREAK_CODE(code) (BIT(7) & code)
#define TWO_BYTE 0xE0

#define MOUSE_LB            BIT(0)
#define MOUSE_RB            BIT(1)
#define MOUSE_MB            BIT(2)
#define FIRST_BYTE          BIT(3)
#define MOUSE_X_SIGNAL      BIT(4)
#define MOUSE_Y_SIGNAL      BIT(5)
#define MOUSE_X_OVERFLOW    BIT(6)
#define MOUSE_Y_OVERFLOW    BIT(7)
#define DISABLE_DATA_REPORT 0xF5
#define ENABLE_DATA_REPORT  0xF4
#define ENABLE_STREAM_MODE  0xEA
#define MOUSE_READ_DATA     0xEB
#define WRITE_BYTE_MOUSE    0xD4

#define ACK 0xFA    
#define NACK 0xFE

/* FUNCTIONS */
int read_status_register(uint8_t* status);
int read_output(uint8_t port, uint8_t* byte, uint8_t mouse);
int write_kbc_command(uint8_t port, uint8_t commandByte);


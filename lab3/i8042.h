#ifndef _LCOM_I8042_H_
#define _LCOM_I8042_H_

#include <lcom/lcf.h>
#include <minix/sysutil.h>

#define BREAK_CODE(code) (code & BIT(7))

#define KBD_IRQ 0x01 
#define STAT_REG 0x64 

/* STATUS REGISTER */
#define OUT_BUF_FULL BIT(0)
#define IN_BUF_FULL BIT(1)
#define AUX BIT(5)
#define TO_ERR BIT(6)
#define PAR_ERR BIT(7)

/* BUFFERS */
#define OUT_BUF 0x60
#define IN_BUF 0x60

/* SCANCODES */
#define ESC_BK_CODE 0x81
#define TWO_BYTE_CODE 0xE0

/* KBC COMMANDS */
#define READ_CMD_B 0x20
#define WRITE_CMD_B 0x60
#define CHECK_KBC 0xAA
#define CHECK_KBD_INTERFACE 0xAB
#define DISABLE_KBD 0xAD
#define ENABLE_KBD 0xAE

/* COMMAND BYTE */
#define KBD_CB_INT BIT(0)
#define KBD_CB_DIS BIT(4)
#define KBD_CB_DIS2 BIT(5)
#define KBD_CB_INT2 BIT(1)

#endif /* _LCOM_I8042_H_ */

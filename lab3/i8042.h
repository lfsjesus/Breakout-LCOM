#ifndef _LCOM_I8042_H_
#define _LCOM_I8042_H_

#include <lcom/lcf.h>
#include <minix/sysutil.h>

#define BREAK_CODE(code) (code & BIT(7))

#define KBD_IRQ 1 //IRQ LINE
#define STAT_REG 0x64 

#define DELAY_US 20000

/* ERRORS */
#define OUT_BUF_FULL BIT(0)
#define IN_BUF_FULL BIT(1)
#define AUX BIT(5)
#define TO_ERR BIT(6)
#define PAR_ERR BIT(7)

/* BUFFERS */
#define OUT_BUF 0x60
#define IN_BUF 0x60

#define ESC_BK_CODE 0x81


#define TWO_BYTE_CODE 0xE0

#endif /* _LCOM_I8042_H_ */

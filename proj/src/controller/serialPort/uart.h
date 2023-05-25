#include <lcom/lcf.h>

//Accessible 8-bit registers

#define COM1_IRQ 4
#define COM1_ADDR 0x3F8


// UART REGISTERS ADDRESSES

#define RBR 0x00 // R   Receiver Buffer Register
#define THR 0x00 // W   Transmitter Holding Register
#define IER 0x01 // R/W Interrupt Enable Register
#define IIR 0x02 // R   Interrupt Identification Reg.
#define FCR 0x02 // W   FIFO Control Register
#define LCR 0x03 // R/W Line Control Register
#define MCR 0x04 // R/W Modem Control Register
#define LSR 0x05 // R   Line Status Register
#define MSR 0x06 // R   Modem Status Register
#define SR 0x07  // R/W Scratchpad Register  

#define DLL 0x00 // Divisor latch LSB  (LCR -> DLAB = 1)
#define DLM 0x01 // Divisor latch MSB  (LCR -> DLAB = 1)

// Line Status Register - lSR

#define LSR_ReceiverData BIT(0)  // There is data to be received
#define LSR_OE BIT(1) // Character received overwritten by another
#define LSR_PE BIT(2) // Character with parity error
#define LSR_FE BIT(3) // Character does not have valid stop bit
#define LSR_BI BIT(4) // Data input is held in the low level for longer than a full word transmission
#define LSR_THRempty BIT(5) // UART is ready to accept a new character for transmitting
#define LSR_TransEmpty BIT(6) // THR and Transmitter Shift Register are empty
#define LSR_FIFOError BIT(7) // parity/framing/break in the fifo, reset to 0 once read  

// BITS 0-4 are reset once LSR is read.
// FIFO buffering may be different - SLIDE14

// INTERRUPT IDENTIFICATION REGISTER  - IIR

#define IIR_INT BIT(0) // 1 if no interrupt pending
#define IIR_INT_ID BIT(1) | BIT(2) | BIT(3) // bit id mask
#define IIR_PRIO_RLS BIT(1) | BIT(2) // Receiver Line Status
#define IIR_PRIO_RDA BIT(2)    // Reived Data Available
#define IIR_PRIO_CTO BIT(2) | BIT(3) // FIFO Character Timeout
#define IIR_PRIO_THRE BIT(1) // Trasmitter Holding Register Empty
#define IIR_PRIO_MS 0 // Modem Status


// INTERRUPT ENABLE REGISTER  - IER

#define IER_RDA BIT(0)  // Enables the Received Data Available Interrupt
#define IER_THRE BIT(1) // Enables the THR empty Interrupt
#define IER_RLS BIT(2)  // Enables the Receiver Line Status interrupt(change in the LSR bits(1-4))
#define IER_MS BIT(3)   // Enables the Modem Status interrupts  


// FIFO Control Register - FCR

#define FCR_EB BIT(0)  //Enables both FIFO's
#define FCR_CR BIT(1)  //Clears all bytes in Receiver FIFO
#define FCR_CX BIT(2)  //Clears all bytes in the XMIT FIFO

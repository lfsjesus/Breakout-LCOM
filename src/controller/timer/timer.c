#include "timer.h"
#include <stdint.h>
#include <lcom/lcf.h>

static int hook_id = TIMER0_IRQ;
uint32_t counter = 0;

int (timer_set_frequency)(uint8_t timer, uint32_t freq) {
  uint8_t config;
  if (timer_get_conf(timer, &config) != OK)
    return !OK;
  
  // Now we need a new config for the timer
  uint8_t control_word = ((TIMER_SEL0 + timer) << 6) | TIMER_LSB_MSB | (config & 0x0F);

  if (sys_outb(TIMER_CTRL, control_word) != OK)
    return !OK;

  // New counter value
  uint16_t new_freq = TIMER_FREQ / freq;
  uint8_t new_freq_lsb, new_freq_msb;
  util_get_LSB(new_freq, &new_freq_lsb);
  util_get_MSB(new_freq, &new_freq_msb);

  if (sys_outb(TIMER_0 + timer, new_freq_lsb) != OK)
    return !OK;
  
  if (sys_outb(TIMER_0 + timer, new_freq_msb) != OK)
    return !OK;
  
  return OK;
}

int (timer_subscribe_int)(uint8_t *bit_no) {
  (*bit_no) = hook_id;
  return sys_irqsetpolicy(TIMER0_IRQ, IRQ_REENABLE, &hook_id);
}

int (timer_unsubscribe_int)() {
  return sys_irqrmpolicy(&hook_id);
}

void (timer_int_handler)() {
  counter += 1;
}

int (timer_get_conf)(uint8_t timer, uint8_t *st) {
  uint8_t command = TIMER_RB_CMD | TIMER_RB_SEL(timer) | TIMER_MSB;

  if (sys_outb(TIMER_CTRL, command) != OK) 
    return !OK;

  if (util_sys_inb(TIMER_0 + timer, st) != OK)
    return !OK;

  return OK;

}

int (timer_display_conf)(uint8_t timer, uint8_t st,
                        enum timer_status_field field) {

  union timer_status_field_val conf;
  
  switch (field) {
    case tsf_all:
      conf.byte = st;
      break;
    case tsf_initial:
      conf.in_mode = (st & (BIT(4) | BIT(5))) >> 4;
      break;
    case tsf_mode:
      conf.count_mode = (st & (BIT(1) | BIT(2) | BIT(3))) >> 1;
      break;
    case tsf_base:
      conf.bcd = st & BIT(0);
      break;
  }

  if (timer_print_config(timer, field, conf) != OK)
    return !OK;
  return OK;
}

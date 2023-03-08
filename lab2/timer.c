#include <lcom/lcf.h>
#include <lcom/timer.h>

#include <stdint.h>

#include "i8254.h"

static int hook_id = 0;
uint32_t counter = 0;

int (timer_set_frequency)(uint8_t timer, uint32_t freq) {
  uint8_t timer_config = 0;

  if (timer_get_conf(timer, &timer_config) != OK) {
    return !OK;
  }
  
  // Extract the last 4 bits of the timer config
  uint8_t timer_config_lsb = timer_config & 0x0F;

  // Construct the new timer configuration using the desired frequency
  uint8_t new_config = (timer << 6) | TIMER_LSB_MSB | timer_config_lsb;

  // Write new config in control register
  if (sys_outb(TIMER_CTRL, new_config) != OK) {
    return !OK;
  }

  // Calculate the timer counter value needed for the desired frequency
  uint16_t timer_counter_value = TIMER_FREQ / freq; 

  // Extract LSB and MSB of the timer counter value
  uint8_t timer_counter_value_lsb, timer_counter_value_msb;
  util_get_LSB(timer_counter_value, &timer_counter_value_lsb);
  util_get_MSB(timer_counter_value, &timer_counter_value_msb);

  // Write the timer counter value in the timer register
  if (sys_outb(TIMER_0 + timer, timer_counter_value_lsb) != OK) 
    return !OK;

  if (sys_outb(TIMER_0 + timer, timer_counter_value_msb) != OK) {
    return !OK;
  }

  return OK;
}

int (timer_subscribe_int)(uint8_t *bit_no) {
  *bit_no = hook_id;
  return sys_irqsetpolicy(TIMER0_IRQ, IRQ_REENABLE, &hook_id);
  
}

int (timer_unsubscribe_int)() {
  return sys_irqrmpolicy(&hook_id);
}

void (timer_int_handler)() {
  counter += 1;
}

int (timer_get_conf)(uint8_t timer, uint8_t *st) {
  uint8_t command = TIMER_RB_CMD | TIMER_RB_COUNT_ | TIMER_RB_SEL(timer);

  if(sys_outb(TIMER_CTRL, command) != OK) {
    return !OK;
  }

  return util_sys_inb(TIMER_0 + timer, st);

}

int (timer_display_conf)(uint8_t timer, uint8_t st,
                        enum timer_status_field field) {
                          
  union timer_status_field_val val; //union to store the value of the field

  switch(field) {
    case tsf_all:
      val.byte = st;
      break;
    case tsf_initial:
      st = st & (BIT(4) | BIT(5));
      st >>= 4;
      val.in_mode = st;
      break;
    case tsf_mode:
      st = st & (BIT(1) | BIT(2) | BIT(3));
      st >>= 1;
      val.count_mode = st;
      break;
    case tsf_base:
      st = st & BIT(0);
      val.bcd = st;
      break;
  }
  
  return timer_print_config(timer, field, val);
}

#include "rtc.h"

static int hook_id = RTC_IRQ;
uint8_t bin_mode;
rtc_time_info rtc_time;

void rtc_config() {
  bin_mode = rtc_binary();
  rtc_update();
}

int rtc_subscribe_int(uint8_t *bit_no) {
  (*bit_no) = hook_id;
  return sys_irqsetpolicy(RTC_IRQ, IRQ_REENABLE, &hook_id);
}

int rtc_unsubscribe_int() {
  return sys_irqrmpolicy(&hook_id);
}

int rtc_output(uint8_t command, uint8_t *output) {
  if (sys_outb(REG_INPUT, command) != OK) {
    return !OK;
  }
  if (util_sys_inb(REG_OUTPUT, output) != OK) {
    return !OK;
  }
  return OK;
}

int rtc_on_update() {
  uint8_t output;
  if (rtc_output(REG_UPDATE_IN_PROGRESS, &output) != OK) {
    return !OK;
  }
  return output & UPDATING;
}

uint8_t rtc_binary() {
  uint8_t output;
  if (rtc_output(REG_COUNT_IN_PROGRESS, &output) != OK) {
    return !OK;
  }
  return output & BIN;
}

uint8_t rtc_is_bcd() {
  return !rtc_binary();
}

uint8_t to_bin(uint8_t bcd) {
  return (10 * (bcd >> 4)) + (bcd & 0x0F);
}

int rtc_update() {
  if (rtc_on_update() != OK) return !OK;

  uint8_t output;

  // Seconds Update
  if (rtc_output(SECS, &output) != OK) {
    return !OK;
  }
  rtc_time.seconds = bin_mode ? output : to_bin(output);

  // Minutes Update
  if (rtc_output(MINS, &output) != OK) {
    return !OK;
  }
  rtc_time.minutes = bin_mode ? output : to_bin(output);

  // Hours Update
  if (rtc_output(HOURS, &output) != OK) {
    return !OK;
  }
  rtc_time.hours = bin_mode ? output : to_bin(output);

  // Day Update
  if (rtc_output(DAY, &output) != OK) {
    return !OK;
  }
  rtc_time.day = bin_mode ? output : to_bin(output);

  // Month Update
  if (rtc_output(MONTH, &output) != OK) {
    return !OK;
  }
  rtc_time.month = bin_mode ? output : to_bin(output);

  // Year Update
  if (rtc_output(YEAR, &output) != OK) {
    return !OK;
  }
  rtc_time.year = bin_mode ? output : to_bin(output);

  return OK;
}


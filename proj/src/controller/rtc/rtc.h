#ifndef RTC_H
#define RTC_H
#include <minix/sysutil.h>
#include <lcom/lcf.h>

#define RTC_IRQ 8
#define REG_INPUT 0x70
#define REG_OUTPUT 0x71

#define REG_UPDATE_IN_PROGRESS 10
#define REG_COUNT_IN_PROGRESS 11

#define SECS 0
#define MINS 2
#define HOURS 4
#define DAY 7
#define MONTH 8
#define YEAR 9

#define BIN BIT(2)
#define UPDATING BIT(7)

typedef struct {
    uint8_t seconds;
    uint8_t minutes;
    uint8_t hours;
    uint8_t day;
    uint8_t month;
    uint8_t year;
} rtc_time_info;

void rtc_config();
uint8_t to_bin(uint8_t bcd);
int rtc_subscribe_int(uint8_t *bit_no);
int rtc_unsubscribe_int();
int rtc_output(uint8_t command, uint8_t *output);
int rtc_on_update();
uint8_t rtc_bcd();
uint8_t rtc_binary();
int rtc_update();

#endif

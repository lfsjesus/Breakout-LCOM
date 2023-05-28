#ifndef LEADERBOARD_H
#define LEADERBOARD_H

#include "../rtc/rtc.h"

typedef struct {
  int level;
  int score;
  rtc_time_info time_info;
  char row_content[64];
} LeaderboardRecord;

LeaderboardRecord* get_records();
int get_entries_filled();
void leaderboard_fill();
void add_leaderboard_record(int level, int score, rtc_time_info *time_info);
int compare_time(rtc_time_info *time1, rtc_time_info *time2);

#endif

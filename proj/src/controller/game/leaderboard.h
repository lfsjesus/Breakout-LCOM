#ifndef LEADERBOARD_H
#define LEADERBOARD_H

#include "../rtc/rtc.h"

typedef struct {
  int level;
  int score;
  rtc_time_info time_info;
  char row_content[64];
} LeaderboardRecord;

/**
 * @brief Get the records object that stores all the records of the game
 * 
 * @return LeaderboardRecord* 
 */
LeaderboardRecord* get_records();

/**
 * @brief Get the number of entries in the leaderboard that are filled
 * 
 * @return int: number of entries
 */
int get_entries_filled();

/**
 * @brief Fetches the leaderboard.txt file to fill game's leaderboard
 * 
 */
void leaderboard_fill();

/**
 * @brief Adds a new record to the leaderboard table if it "fits" there or if it is better than any one.
 * 
 * @param level game level
 * @param score number of points
 * @param time_info struct that holds the current time
 */
void add_leaderboard_record(int level, int score, rtc_time_info *time_info);
int compare_time(rtc_time_info *time1, rtc_time_info *time2);

#endif

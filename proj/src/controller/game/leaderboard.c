#include "leaderboard.h"
#include <lcom/lcf.h>

// Change this to your own path
#define SAVE_PATH "/home/lcom/labs/g4_proj/proj/src/data/leaderboard.txt" 

#define MAX_RECORDS 5

static int entriesFilled = 0;
static LeaderboardRecord records[MAX_RECORDS];

LeaderboardRecord* get_records() {
  return records;
}

int get_entries_filled() {
  return entriesFilled;
}

void leaderboard_fill() {
    FILE *file = fopen(SAVE_PATH, "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    char line[100];

    // Read records from the file
    entriesFilled = 0;
    while (entriesFilled < MAX_RECORDS && fgets(line, sizeof(line), file) != NULL) {
        sscanf(line, "%d |          %04d |    %02hhu:%02hhu | %02hhu/%02hhu/%hhu",
               &records[entriesFilled].level, &records[entriesFilled].score,
               &records[entriesFilled].time_info.hours, &records[entriesFilled].time_info.minutes,
               &records[entriesFilled].time_info.day, &records[entriesFilled].time_info.month,
               &records[entriesFilled].time_info.year);

        strcpy(records[entriesFilled].row_content, line);
        entriesFilled++;
    }

    fclose(file);

    for (int i = 0; i < entriesFilled - 1; i++) {
        for (int j = i + 1; j < entriesFilled; j++) {
            if (records[i].level < records[j].level
                || (records[i].level == records[j].level && records[i].score < records[j].score)
                || (records[i].level == records[j].level && records[i].score == records[j].score &&
                    compare_time(&records[i].time_info, &records[j].time_info) > 0)) {
                LeaderboardRecord temp = records[i];
                records[i] = records[j];
                records[j] = temp;
            }
        }
    }
}

void add_leaderboard_record(int level, int score, rtc_time_info *time_info) {
    leaderboard_fill();

    // Check if the new record is better than any existing record or if there's space to add it
    int insertIndex = -1; 

    // Iterate through the existing records to find the insertion index
    for (int i = 0; i < entriesFilled; i++) {
        if (level > records[i].level ||
            (level == records[i].level && score > records[i].score) ||
            (level == records[i].level && score == records[i].score && compare_time(time_info, &records[i].time_info) < 0)) {
            insertIndex = i;
            break; 
        }
    }

    if (insertIndex == -1 && entriesFilled < MAX_RECORDS) {
        insertIndex = entriesFilled;
        entriesFilled++; 
    }
    else if (insertIndex == -1) {
        return;
    }

    // Shift right the ones that are after the insertion index
    for (int i = entriesFilled - 1; i > insertIndex; i--) {
        records[i] = records[i - 1];
    }

    // Insert the new record
    records[insertIndex].level = level;
    records[insertIndex].score = score;
    records[insertIndex].time_info = *time_info;
    sprintf(records[insertIndex].row_content, "%d |          %04d |    %02hhu:%02hhu | %02hhu/%02hhu/%hhu\n",
            level, score, time_info->hours, time_info->minutes, time_info->day, time_info->month, time_info->year);

    

    // Update the file with the new leaderboard records
    FILE *file = fopen(SAVE_PATH, "w");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    for (int i = 0; i < entriesFilled; i++) {
        fprintf(file, "%s", records[i].row_content);
    }

    fclose(file);
}

int compare_time(rtc_time_info *time1, rtc_time_info *time2) {
    if (time1->year < time2->year) {
        return -1;
    } else if (time1->year > time2->year) {
        return 1;
    } else {
        if (time1->month < time2->month) {
            return -1;
        } else if (time1->month > time2->month) {
            return 1;
        } else {
            if (time1->day < time2->day) {
                return -1;
            } else if (time1->day > time2->day) {
                return 1;
            } else {
                if (time1->hours < time2->hours) {
                    return -1;
                } else if (time1->hours > time2->hours) {
                    return 1;
                } else {
                    if (time1->minutes < time2->minutes) {
                        return -1;
                    } else if (time1->minutes > time2->minutes) {
                        return 1;
                    } else {
                        return 0;
                    }
                }
            }
        }
    }
}


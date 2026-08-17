#ifndef RTC_MANAGER_H
#define RTC_MANAGER_H

#include <RTClib.h>

extern RTC_DS3231 rtc;

// Initializes the RTC
bool initRTC();

// Waits until today's scheduled play time
void waitForPlayTime();

// Returns true if it is currently time to play
bool isPlayTime();

// Prints the current date/time to Serial
void printCurrentTime();

// Returns today's randomized play time
DateTime getTodaysPlayTime();

#endif

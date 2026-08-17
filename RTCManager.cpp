#include "RTCManager.h"
#include "Settings.h"
#include "Power.h"

#include <Wire.h>

RTC_DS3231 rtc;

static DateTime playTime;
static bool playTimeGenerated = false;

bool initRTC()
{
    Wire.begin(SDA_PIN, SCL_PIN);

    if (!rtc.begin())
    {
        Serial.println("RTC not detected.");
        return false;
    }

    if (rtc.lostPower())
    {
        // Set RTC to the compile time
        rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
        Serial.println("RTC lost power. Time reset.");
    }

    return true;
}

DateTime getTodaysPlayTime()
{
    if (playTimeGenerated)
        return playTime;

    DateTime now = rtc.now();

    randomSeed(now.unixtime());

    int offset =
        random(-RANDOM_OFFSET_MINUTES,
               RANDOM_OFFSET_MINUTES + 1);

    int hour = PLAY_HOUR;
    int minute = PLAY_MINUTE + offset;

    while (minute < 0)
    {
        minute += 60;
        hour--;
    }

    while (minute >= 60)
    {
        minute -= 60;
        hour++;
    }

    while (hour < 0)
        hour += 24;

    while (hour >= 24)
        hour -= 24;

    playTime = DateTime(
        now.year(),
        now.month(),
        now.day(),
        hour,
        minute,
        0);

    playTimeGenerated = true;

    return playTime;
}

bool isPlayTime()
{
    DateTime now = rtc.now();

    return now.unixtime() >=
           getTodaysPlayTime().unixtime();
}

void waitForPlayTime()
{
    while (!isPlayTime())
    {
        printCurrentTime();

        if (batteryCritical())
        {
            Serial.println("Battery critical.");
            goToSleepUntilTomorrow();
        }

        delay(30000);
    }
}

void printCurrentTime()
{
    DateTime now = rtc.now();

    Serial.print(now.year());
    Serial.print("-");

    Serial.print(now.month());
    Serial.print("-");

    Serial.print(now.day());

    Serial.print(" ");

    Serial.print(now.hour());

    Serial.print(":");

    if (now.minute() < 10)
        Serial.print("0");

    Serial.println(now.minute());
}

#include <Arduino.h>
#include "Power.h"
#include "Settings.h"

#define ADC_MAX 4095.0
#define ADC_REF 3.30

// Change this if your resistor divider uses different values
const float R1 = 100000.0;
const float R2 = 100000.0;

void initPower()
{
    analogReadResolution(12);
}

float readBatteryVoltage()
{
    const int samples = 20;

    long total = 0;

    for(int i=0;i<samples;i++)
    {
        total += analogRead(BATTERY_PIN);
        delay(2);
    }

    float adc = total / (float)samples;

    float measured =
        (adc / ADC_MAX) * ADC_REF;

    float battery =
        measured * ((R1 + R2) / R2);

    return battery;
}

int readBatteryPercent()
{
    float v = readBatteryVoltage();

    if(v >= 4.20) return 100;
    if(v <= 3.30) return 0;

    return (int)((v - 3.30) * 111.1);
}

bool batteryOK()
{
    return readBatteryVoltage() > LOW_BATTERY;
}

bool batteryCritical()
{
    return readBatteryVoltage() < CRITICAL_BATTERY;
}

void printBatteryStatus()
{
    Serial.print("Battery: ");

    Serial.print(readBatteryVoltage(),2);

    Serial.print(" V   ");

    Serial.print(readBatteryPercent());

    Serial.println("%");
}

void goToSleepMinutes(int minutes)
{
    uint64_t us =
        (uint64_t)minutes * 60ULL * 1000000ULL;

    esp_sleep_enable_timer_wakeup(us);

    esp_deep_sleep_start();
}

void goToSleepUntilTomorrow()
{
    goToSleepMinutes(24 * 60);
}

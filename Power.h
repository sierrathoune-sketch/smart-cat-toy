#ifndef POWER_H
#define POWER_H

void initPower();

float readBatteryVoltage();

int readBatteryPercent();

bool batteryOK();

bool batteryCritical();

void printBatteryStatus();

void goToSleepMinutes(int minutes);

void goToSleepUntilTomorrow();

#endif

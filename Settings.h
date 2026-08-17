#ifndef SETTINGS_H
#define SETTINGS_H

//==============================
// HARDWARE PINS
//==============================

// Servo output
#define SERVO_PIN 2      // XIAO D0 (change if needed)

// Battery voltage monitor
#define BATTERY_PIN A1

// RTC (DS3231)
#define SDA_PIN 6         // D4
#define SCL_PIN 7         // D5

//==============================
// SERVO POSITIONS
//==============================

const int HOME_POSITION = 90;

const int TWITCH_POSITION = 105;

const int SMALL_PULL = 120;

const int MEDIUM_PULL = 140;

const int BIG_PULL = 160;

//==============================
// PLAY SESSION
//==============================

const int PLAY_MINUTES_MIN = 8;

const int PLAY_MINUTES_MAX = 15;

//==============================
// DAILY START TIME
//==============================

// 6:00 PM

const int PLAY_HOUR = 18;

const int PLAY_MINUTE = 0;

// Random start offset

const int RANDOM_OFFSET_MINUTES = 30;

//==============================
// BATTERY
//==============================

const float LOW_BATTERY = 3.45;

const float CRITICAL_BATTERY = 3.30;

//==============================
// SERVO SPEED
//==============================

// Smaller = slower

const int SERVO_SPEED = 12;

//==============================
// MOVEMENT PROBABILITIES
//==============================

const int TWITCH_CHANCE = 30;

const int HUNT_CHANCE = 20;

const int DART_CHANCE = 20;

const int STALK_CHANCE = 20;

const int PANIC_CHANCE = 10;

#endif

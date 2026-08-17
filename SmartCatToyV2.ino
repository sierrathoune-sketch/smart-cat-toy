// =====================================================
// SmartCatToyV2.ino
// Main program for ESP32-C3 Smart Cat Toy
// Hardware:
//   - ESP32-C3
//   - MG90S Servo on GPIO 18
//   - DS3231 RTC
//   - Battery monitor on GPIO 0
// =====================================================

#include <Arduino.h>
#include "RTCManager.h"
#include "Power.h"
#include "CatBehavior.h"

// ---------------- USER SETTINGS ----------------

// Daily play time (24-hour format)
const int PLAY_HOUR   = 18;   // 6:00 PM
const int PLAY_MINUTE = 0;

// Random start offset in minutes
const int RANDOM_OFFSET_MINUTES = 30;

// -----------------------------------------------

void setup() {

  Serial.begin(115200);
  delay(1000);

  Serial.println("\n=== Smart Cat Toy V2 Starting ===");

  // Initialize subsystems
  initPower();
  initRTC();
  initBehavior();
  float vbat = readBatteryVoltage();

  Serial.print("Battery voltage: ");
  Serial.println(vbat, 2);

  if (!batteryOK(vbat)) {

    Serial.println("Battery too low. Sleeping for 24 hours.");

    sleepForHours(24);

    return;
  }

  // Wait until today's scheduled play time
  waitUntilPlayTime(
      PLAY_HOUR,
      PLAY_MINUTE,
      RANDOM_OFFSET_MINUTES
  );

  Serial.println("Starting play session...");

  runDailySession();

  Serial.println("Play session complete.");

  // Sleep until tomorrow
  sleepUntilTomorrow(
      PLAY_HOUR,
      PLAY_MINUTE
  );
}

void loop() {
  // Never used because we deep sleep after setup()
}

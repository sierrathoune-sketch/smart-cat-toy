# smart-cat-toy
C++ code for realistic prey movement for a cat toy using a string on a door frame using AI-assisted coding.

# SmartCatToyV2.ino
<img width="1071" height="977" alt="image" src="https://github.com/user-attachments/assets/3f0218dd-3c66-4812-802b-16c93a60db5b" />

## Start-up sequence 
ESP32 wakes up > initialize RTC, power, and servo system > read battery voltage > if battery low, sleep 24 h > wait until scheduled play time > run randomized play session > deep sleep until tomorrow

## Change play times by editing these lines:
const int PLAY_HOUR   = 18;   // 6 PM
const int PLAY_MINUTE = 0;

For example, 08:00 = 8, 0 / 12:30 12, 30 / 21:15 21, 15

## Randomization
const int RANDOM_OFFSET_MINUTES = 30;

If set to 30, toy may start from 17:30 - 18🕥

## Battery Protection
Voltage threshold set in Power module.
float vbat = readBatteryVoltage();

if (!batteryOK(vbat)) {
    sleepForHours(24);
}

## Required Librariies
Install these in [Arduino IDE](https://docs.arduino.cc/software/ide-v2/tutorials/getting-started/ide-v2-downloading-and-installing/)
- ESP32 by Espressif Systems (Board Manager)
- RTClib by Adafruit
- ESP32Servo by Kevin Harrington / John K. Bennett

## Create Folders
In the same Arduino sketch folder:
SmartCatToyV2/
 ├── SmartCatToyV2.ino
 ├── RTCManager.h
 ├── RTCManager.cpp
 ├── Power.h
 ├── Power.cpp
 ├── CatBehavior.h
 └── CatBehavior.cpp

# ServoMotion
## Motion Types
Behavior - Description
- Twitch - Tiny movements like an insect
- Small Pull - Gentle tug
- Medium Pull - Curious mouse movement
- Big Pull - Strong prey movement
- Dart - Quick escape
- Stalk - Slow creepying motion
- Panic - Rapid shaking like trapped prey

# Power
Protects battery from excessive discharge and avoids servo trying to run when the battery is too low.
Battery Voltage - Behavior
>= 3.70 V - Full play session
3.45 - 3.70 V - Shortened play session
3.30 - 3.45 V - Skip play, sleep until tomorrow
< 3.30 V - Emergency shutdown until recharged

# RTCManager
Configure 
PLAY_HOUR = 18
PLAY_MINUTE = 0
RANDOM_OFFSET = 30

To start at random time each day so there is not an exact schedule.

# CatBehavior
Behavior - Description - Probability
- Freeze - Completely still - 15%
- Investigate - Small curious movements - 20%
- Forage - Slow creeping - 20%
- Escape - Quick dart away - 20%
- Panic - Rapid jerks - 15%
- Rest - Long pause - 10%

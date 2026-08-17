#ifndef SERVO_MOTION_H
#define SERVO_MOTION_H

#include <ESP32Servo.h>

void initServo();
void moveServoSmooth(int targetAngle);
void twitch();
void smallPull();
void mediumPull();
void bigPull();
void dart();
void stalk();
void panic();
void goHome();

#endif

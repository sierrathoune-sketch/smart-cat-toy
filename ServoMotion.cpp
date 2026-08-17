#include "ServoMotion.h"
#include "Settings.h"

Servo catServo;

int currentPosition = HOME_POSITION;

void initServo()
{
    catServo.setPeriodHertz(50);
}

void attachServo()
{
    if (!catServo.attached())
    {
        catServo.attach(SERVO_PIN);
        delay(80);
    }
}

void detachServo()
{
    if (catServo.attached())
    {
        delay(100);
        catServo.detach();
    }
}

void moveServoSmooth(int target)
{
    attachServo();

    int direction = (target > currentPosition) ? 1 : -1;

    while (currentPosition != target)
    {
        int distance = abs(target - currentPosition);

        int speedDelay;

        // Smooth acceleration/deceleration
        if (distance > 35)
            speedDelay = 4;
        else if (distance > 20)
            speedDelay = 7;
        else if (distance > 10)
            speedDelay = 10;
        else
            speedDelay = 15;

        currentPosition += direction;

        catServo.write(currentPosition);

        delay(speedDelay);
    }

    delay(120);

    detachServo();
}

void goHome()
{
    moveServoSmooth(HOME_POSITION);
}

void twitch()
{
    moveServoSmooth(TWITCH_POSITION);

    delay(random(80,200));

    goHome();
}

void smallPull()
{
    moveServoSmooth(SMALL_PULL);

    delay(random(200,500));

    goHome();
}

void mediumPull()
{
    moveServoSmooth(MEDIUM_PULL);

    delay(random(300,700));

    goHome();
}

void bigPull()
{
    moveServoSmooth(BIG_PULL);

    delay(random(500,1200));

    goHome();
}

void dart()
{
    attachServo();

    catServo.write(BIG_PULL);

    currentPosition = BIG_PULL;

    delay(150);

    catServo.write(HOME_POSITION);

    currentPosition = HOME_POSITION;

    delay(150);

    detachServo();
}

void stalk()
{
    moveServoSmooth(100);

    delay(400);

    moveServoSmooth(108);

    delay(500);

    moveServoSmooth(115);

    delay(700);

    moveServoSmooth(125);

    delay(600);

    goHome();
}

void panic()
{
    attachServo();

    for(int i=0;i<8;i++)
    {
        catServo.write(120);

        delay(60);

        catServo.write(95);

        delay(60);
    }

    currentPosition = 95;

    goHome();
}

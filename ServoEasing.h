#ifndef SERVO_EASING_H
#define SERVO_EASING_H

void smoothMove(int startAngle,
                int endAngle,
                int moveTime);

#endif

void breathing()
{
    for(int i=0;i<5;i++)
    {
        catServo.write(149);

        delay(80);

        catServo.write(151);

        delay(80);
    }
}

delay(random(5000,25000));

#include <math.h>
#include "ServoEasing.h"
#include "ServoMotion.h"

extern Servo catServo;

void smoothMove(int start,
                int end,
                int duration)
{
    const int fps = 50;

    int frames =
        duration / (1000 / fps);

    if(frames < 1)
        frames = 1;

    for(int i=0;i<=frames;i++)
    {
        float t =
            (float)i / frames;

        // cosine easing

        float eased =
            (1 - cos(t * PI)) / 2;

        int angle =
            start +
            (end - start) * eased;

        catServo.write(angle);

        delay(1000/fps);
    }
}

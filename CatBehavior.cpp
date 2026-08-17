#include "CatBehavior.h"
#include "ServoMotion.h"
#include "Settings.h"
#include "Power.h"

enum Behavior
{
    FREEZE,
    INVESTIGATE,
    FORAGE,
    ESCAPE,
    PANIC,
    REST
};

static Behavior chooseBehavior()
{
    int r = random(100);

    if (r < 15) return FREEZE;
    if (r < 35) return INVESTIGATE;
    if (r < 55) return FORAGE;
    if (r < 75) return ESCAPE;
    if (r < 90) return PANIC;

    return REST;
}

void initBehavior()
{
    randomSeed(micros());
}

void freezeBehavior()
{
    delay(random(3000,12000));
}

void investigateBehavior()
{
    twitch();

    delay(random(500,1500));

    twitch();

    delay(random(1000,3000));

    smallPull();

    delay(random(2000,5000));
}

void forageBehavior()
{
    stalk();

    delay(random(2000,6000));

    mediumPull();

    delay(random(2000,4000));
}

void escapeBehavior()
{
    dart();

    delay(random(1000,3000));

    bigPull();

    delay(random(2000,5000));
}

void panicBehavior()
{
    panic();

    delay(random(4000,8000));
}

void restBehavior()
{
    delay(random(10000,45000));
}

void runDailySession()
{
    unsigned long duration =
        random(PLAY_MINUTES_MIN * 60000UL,
               PLAY_MINUTES_MAX * 60000UL);

    unsigned long start = millis();

    while ((millis() - start) < duration)
    {
        if (!batteryOK())
            break;

        switch (chooseBehavior())
        {
            case FREEZE:
                freezeBehavior();
                break;

            case INVESTIGATE:
                investigateBehavior();
                break;

            case FORAGE:
                forageBehavior();
                break;

            case ESCAPE:
                escapeBehavior();
                break;

            case PANIC:
                panicBehavior();
                break;

            case REST:
                restBehavior();
                break;
        }
    }

    goHome();
}

#pragma once

#include <QString>

namespace utils
{
    inline float pi()
    {
        return 3.14159265;
    }

    inline float toRadians(float degrees)
    {
        return pi() * degrees / 180;
    }

    inline float toDegrees(float radians)
    {
        return 180 * radians / pi();
    }
    inline QString showableTime(int ms)
    {
        QChar character(0x30);
        ms/=10;
        int csec = ms%100;
        ms/=100;
        int sec = ms%60;
        ms/=60;
        QString time;
        time= QString ("%1:%2:%3")
               .arg(ms,2,10,character)
               .arg(sec,2,10,character)
               .arg(csec,2,10,character);
        return time;

    }

}

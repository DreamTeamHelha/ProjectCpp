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
        ms/=10;
        int csec = ms%100;
        ms/=100;
        int sec = ms%60;
        ms/=60;
        QString time = QString::number(ms)+":"+QString::number(sec)+":"+QString::number(csec)+"''";
        return time;

    }

}

#pragma once

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

}

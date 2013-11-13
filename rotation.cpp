#include "rotation.h"
#include "vector.h"
#include <cmath>
#include "mathutils.h"

const float Rotation::m_maxAngle = 2 * mathutils::pi();

Rotation::operator Vector() const
{
    return Vector(std::cos(m_angle), std::sin(m_angle));
}

void Rotation::setAngle(float radangle)
{
    m_angle = radangle;

    while (m_angle < 0)
    {
        m_angle += m_maxAngle;
    }

    while (m_angle >= m_maxAngle)
    {
        m_angle -= m_maxAngle;
    }
}

bool operator<(const Rotation& left, const Rotation & right)
{
    if (right == left)
        return false;
    else
        return (right - left).angle() <= mathutils::pi();
}

bool operator>(const Rotation& left, const Rotation & right)
{
    if (right == left)
        return false;
    else
        return (right - left).angle() >= mathutils::pi();
}

bool operator<=(const Rotation& left, const Rotation & right)
{
    if (right == left)
        return true;
    else
        return (right - left).angle() <= mathutils::pi();
}

bool operator>=(const Rotation& left, const Rotation & right)
{
    if (right == left)
        return true;
    else
        return (right - left).angle() >= mathutils::pi();
}

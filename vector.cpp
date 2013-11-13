#include "vector.h"
#include "rotation.h"
#include <cmath>

float Vector::length() const
{
    return std::sqrt(m_x*m_x + m_y*m_y);
}

void Vector::normalize()
{
    if (m_x == 0.f && m_y == 0.f)
        return;

    float length = this->length();

    m_x /= length;
    m_y /= length;
}

Vector Vector::normalized() const
{
    Vector vector = *this;
    vector.normalize();
    return vector;
}

Vector::operator Rotation() const
{
    Vector sinCos = normalized();
    if (sinCos.x() >= 0)
    {
        return Rotation::radians(std::asin(sinCos.y()));
    }
    else if (sinCos.y() >= 0)
    {
        return Rotation::radians(std::acos(sinCos.x()));
    }
    else
    {
        return Rotation::radians(-std::acos(sinCos.x()));
    }
}

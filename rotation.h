#pragma once

#include <iostream>
#include "utils.h"

class Vector;

class Rotation
{
public:

    Rotation(float radangle=0.f)
    {
        setAngle(radangle);
    }

    virtual ~Rotation()
    {}

    ///
    /// Getter
    ///
    float angle() const
    {
        return m_angle;
    }

    ///
    /// Setter
    ///
    void setAngle(float radangle);

    ///
    /// Conversions
    ///
    float radians() const
    {
        return m_angle;
    }

    float degrees() const
    {
        return utils::toDegrees(m_angle);
    }

    static Rotation radians(float radians)
    {
        return Rotation(radians);
    }

    static Rotation degrees(float degrees)
    {
        return Rotation(utils::toRadians(degrees));
    }

    explicit operator Vector() const;

private:

    float m_angle;
    static const float m_maxAngle;
};

///
/// Operateur de flux
///
inline std::ostream& operator<<(std::ostream& out, const Rotation& rotation)
{
    out << "Rotation(angle=" << rotation.degrees() << ")";
    return out;
}

///
/// Operateur de comparaison
///
inline bool operator==(const Rotation& left, const Rotation& right)
{
    return left.angle() == right.angle();
}

inline bool operator!=(const Rotation& left, const Rotation& right)
{
    return left.angle() != right.angle();
}

bool operator<(const Rotation& left, const Rotation& right);
bool operator>(const Rotation& left, const Rotation& right);
bool operator<=(const Rotation& left, const Rotation& right);
bool operator>=(const Rotation& left, const Rotation& right);

///
/// Operateur mathématiques
///
inline Rotation operator+(const Rotation& left, const Rotation& right)
{
    return Rotation(left.angle() + right.angle());
}

inline Rotation operator-(const Rotation& left, const Rotation& right)
{
    return Rotation(left.angle() - right.angle());
}

inline Rotation operator*(const Rotation& rotation, float factor)
{
    return Rotation(rotation.angle() * factor);
}

inline Rotation operator/(const Rotation& rotation, float factor)
{
    return Rotation(rotation.angle() / factor);
}

inline Rotation operator+=(Rotation& left, const Rotation& right)
{
    left.setAngle(left.angle() + right.angle());
    return left;
}

inline Rotation& operator-=(Rotation& left, const Rotation& right)
{
    left.setAngle(left.angle() - right.angle());
    return left;
}

inline Rotation& operator*=(Rotation& rotation, float factor)
{
    rotation.setAngle(rotation.angle() * factor);
    return rotation;
}

inline Rotation& operator/=(Rotation& rotation, float factor)
{
    rotation.setAngle(rotation.angle() / factor);
    return rotation;
}

inline Rotation operator-(const Rotation& rotation)
{
    return Rotation(rotation.angle() + utils::pi());
}

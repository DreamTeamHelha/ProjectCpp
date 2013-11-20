#pragma once

#include <iostream>
#include <QPointF>
#include <QVector2D>
#include <Box2D/Box2D.h>

class Rotation;

///
/// Classe représentant un point, un vecteur, ou une force
///
class Vector
{
public:

    Vector(float x=0.f, float y=0.f) :
        m_x(x),
        m_y(y)
    {
    }

    Vector(const QPointF& other) :
        m_x(other.x()),
        m_y(other.y())
    {
    }

    Vector(const QVector2D& other) :
        m_x(other.x()),
        m_y(other.y())
    {
    }

    Vector(const b2Vec2& other) :
        m_x(other.x),
        m_y(other.y)
    {
    }

    virtual ~Vector()
    {
    }

    ///
    /// Getters
    ///
    float x() const
    {
        return m_x;
    }

    float y() const
    {
        return m_y;
    }

    ///
    /// Setters
    ///
    void setX(float x)
    {
        m_x = x;
    }

    void setY(float y)
    {
        m_y = y;
    }

    ///
    /// Conversions
    ///
    operator QPointF() const
    {
        return QPointF(m_x, m_y);
    }

    operator QVector2D() const
    {
        return QVector2D(m_x, m_y);
    }

    operator b2Vec2() const
    {
        return b2Vec2(m_x, m_y);
    }

    explicit operator Rotation() const;

    ///
    /// Calcule et retourne la taille du vecteur.
    ///
    float  length() const;
    ///
    /// Normalise le vecteur.
    ///
    void   normalize();
    ///
    /// Retourne une copie normalisée du vecteur.
    ///
    Vector normalized() const;

private:

    float m_x;
    float m_y;
};

///
/// Opérateurs
///

///
/// Flux
///
inline std::ostream& operator<<(std::ostream& out, const Vector& vector)
{
    out << "Vector(x=" << vector.x() << "; y=" << vector.y() << ")";
    return out;
}

///
/// Comparaison
///
inline bool operator==(const Vector& left, const Vector& right)
{
    return left.x() == right.x() && left.y() == right.y();
}

inline bool operator!=(const Vector& left, const Vector& right)
{
    return left.x() != right.x() || left.y() != right.y();
}

///
/// Opérations mathématiques
///
inline Vector operator+(const Vector& left, const Vector& right)
{
    return Vector(left.x()+right.x(), left.y()+right.y());
}

inline Vector operator-(const Vector& left, const Vector& right)
{
    return Vector(left.x()-right.x(), left.y()-right.y());
}

inline Vector operator*(const Vector& left, const Vector& right)
{
    return Vector(left.x()*right.x(), left.y()*right.y());
}

inline Vector operator/(const Vector& left, const Vector& right)
{
    return Vector(left.x()/right.x(), left.y()/right.y());
}

inline Vector operator*(const Vector& left, float factor)
{
    return Vector(left.x()*factor, left.y()*factor);
}

inline Vector operator/(const Vector& left, float factor)
{
    return Vector(left.x()/factor, left.y()/factor);
}

inline Vector& operator+=(Vector& left, const Vector& right)
{
    left.setX(left.x() + right.x());
    left.setY(left.y() + right.y());
    return left;
}

inline Vector& operator-=(Vector& left, const Vector& right)
{
    left.setX(left.x() - right.x());
    left.setY(left.y() - right.y());
    return left;
}

inline Vector& operator*=(Vector& left, const Vector& right)
{
    left.setX(left.x() * right.x());
    left.setY(left.y() * right.y());
    return left;
}

inline Vector& operator/=(Vector& left, const Vector& right)
{
    left.setX(left.x() / right.x());
    left.setY(left.y() / right.y());
    return left;
}

inline Vector& operator*=(Vector& left, float factor)
{
    left.setX(left.x() * factor);
    left.setY(left.y() * factor);
    return left;
}

inline Vector& operator/=(Vector& left, float factor)
{
    left.setX(left.x() / factor);
    left.setY(left.y() / factor);
    return left;
}

inline Vector operator-(const Vector& vector)
{
    return Vector(-vector.x(), -vector.y());
}


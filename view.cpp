#include "view.h"

View::View(const Vector& position, float zoom) :
    m_position(position),
    m_zoom(zoom)
{
}

const Vector& View::position() const
{
    return m_position;
}

void View::setPosition(const Vector &position)
{
    m_position = position;
}

float View::zoom() const
{
    return m_zoom;
}

void View::setZoom(float zoom)
{
    m_zoom = zoom;
}

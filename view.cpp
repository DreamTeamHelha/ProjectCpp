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

View View::interp(const View &start, const View &end, float factor)
{
    View view;

    // interpolation de la position
    if( (end.position() - start.position()).length() < 1.f)
    {
        view.setPosition(end.position());
    }
    else
    {
        view.setPosition( start.position() + (end.position() - start.position())*factor );
    }

    // interpolation du zoom
    view.setZoom( start.zoom() + (end.zoom() - start.zoom())*factor );
    return view;
}

#pragma once

#include "vector.h"

///
/// Contient les informations relatives à la vue in-game
///
class View
{
public:

    View(const Vector& position = Vector(0,0), float zoom=1.f);

    ///
    /// Position de la caméra
    ///
    const Vector& position() const;
    void setPosition(const Vector& position);

    ///
    /// Facteur de zoom (1 = pas de zoom; <1 = dézoom; >1 = zoom)
    ///
    float zoom() const;
    void setZoom(float zoom);

private:

    Vector m_position;
    float  m_zoom;
};

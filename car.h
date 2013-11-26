#pragma once

#include "object.h"
#include "objectfactory.h"
#include "tilemap.h"

class Car : public Object
{
public:

    Car(QGraphicsItem *graphicsItem, b2Body *physicsBody);

    void step(qreal throttle, qreal brakes, qreal steering);

    Tilemap *tilemap() const;
    void setTilemap(Tilemap *tilemap);

private:

    Tilemap *m_tilemap;
};


class CarFactory : public ObjectFactory
{
public:

    Object *create() const;
};

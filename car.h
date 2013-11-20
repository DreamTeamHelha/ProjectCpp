#pragma once

#include "object.h"
#include "objectfactory.h"

class Car : public Object
{
public:

    Car(QGraphicsItem *graphicsItem, b2Body *physicsBody);

    void step(qreal throttle, qreal brakes, qreal steering);
};


class CarFactory : public ObjectFactory
{
public:

    Object *create() const;
};

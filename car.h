#pragma once

#include "object.h"

class Car : public Object
{
public:

    Car(QGraphicsItem *graphicsItem, b2Body *physicsBody);

    void step(qreal throttle, qreal brakes, qreal steering);
};

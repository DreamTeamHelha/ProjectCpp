#pragma once

#include "object.h"
#include "objectfactory.h"

class Box : public Object
{
public:

    Box(QGraphicsItem *graphicsItem, b2Body *physicsBody);
};


class BoxFactory : public ObjectFactory
{
public:

    Object *create() const;
};

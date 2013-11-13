#pragma once

#include "object.h"

class Box : public Object
{
public:

    Box(QGraphicsItem *graphicsItem, b2Body *physicsBody);
};


#pragma once
#include "object.h"
#include "objectfactory.h"

class Checkpoint : public Object
{
public:
    Checkpoint(QGraphicsItem *graphicsItem, b2Body *physicsBody);
};

class CheckpointFactory : public ObjectFactory
{
public:

    Object *create() const;
};

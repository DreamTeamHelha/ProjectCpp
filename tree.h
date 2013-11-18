#pragma once

#include "object.h"
#include "objectfactory.h"

class Tree : public Object
{
public:
    Tree(QGraphicsItem *graphicsItem, b2Body *physicsBody);

};

class TreeFactory : public ObjectFactory
{
public:

    Object *create() const;
};

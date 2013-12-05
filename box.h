#pragma once

#include "object.h"
#include "objectfactory.h"

class Box : public Object
{
public:

    Box(QGraphicsItem *graphicsItem=nullptr, b2Body *physicsBody=nullptr);
    Box(const Box &b);
    Box& operator=(const Box &b);
};


class BoxFactory : public ObjectFactory
{
public:

    /// Crée un objet 'Box' et le retourne
    Object *create() const;
};

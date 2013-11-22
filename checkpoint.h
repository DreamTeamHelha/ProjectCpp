#pragma once
#include "object.h"
#include "objectfactory.h"

class Checkpoint : public Object
{
private:
    bool m_touched;
    bool m_isFinish;
public:
    Checkpoint(QGraphicsItem *graphicsItem, b2Body *physicsBody);
    void touch();
    bool touched();

};

class CheckpointFactory : public ObjectFactory
{
public:

    Object *create() const;
};

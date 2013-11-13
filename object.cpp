#include "object.h"
#include "mathutils.h"

Object::Object(QGraphicsItem *graphicsItem, b2Body *physicsBody) :
    m_graphicsItem(graphicsItem),
    m_physicsBody(physicsBody)
{
}

Object::~Object()
{
    // rien à faire
}


QGraphicsItem *Object::graphicsItem() const
{
    return m_graphicsItem;
}

b2Body *Object::physicsBody() const
{
    return m_physicsBody;
}


void Object::update()
{
    using mathutils::toDegrees;

    if (m_graphicsItem && m_physicsBody)
    {
        m_graphicsItem->setPos(m_physicsBody->GetPosition().x, m_physicsBody->GetPosition().y);
        m_graphicsItem->setRotation(toDegrees(m_physicsBody->GetAngle()));
    }
}

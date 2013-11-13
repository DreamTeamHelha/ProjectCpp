#include "box.h"
#include "mathutils.h"

Box::Box(QGraphicsItem *graphicsItem, b2Body *physicsBody) :
    Object(graphicsItem, physicsBody)
{
}

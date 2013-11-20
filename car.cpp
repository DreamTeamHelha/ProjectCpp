#include "car.h"
#include "mathutils.h"
#include <cmath>
#include <iostream>
#include "vector.h"
#include "rotation.h"
#include <QGraphicsRectItem>
#include <Box2D/Box2D.h>
#include "scene.h"

Car::Car(QGraphicsItem *graphicsItem, b2Body *physicsBody) :
    Object(graphicsItem, physicsBody)
{
}

void Car::step(qreal throttle, qreal brakes, qreal steering)
{
    if (physicsBody())
    {
        float accel = 0;

        if (throttle > 0)
            accel += 200000;
        if (brakes > 0)
           accel -= 100000;

        Vector vAccel = (Vector)(Rotation::radians(physicsBody()->GetAngle()));
        vAccel *= accel;

        physicsBody()->ApplyForceToCenter(vAccel);

        if (steering != 0)
            physicsBody()->ApplyTorque(steering*200000);
    }
}


Object *CarFactory::create() const
{
    using mathutils::toRadians;

    if (!scene())
        return nullptr;

    // création de la partie visible
    QGraphicsRectItem *graphicsRect = new QGraphicsRectItem(-20, -10, 40, 20);
    graphicsRect->setPos(position());
    graphicsRect->setRotation(rotation().degrees());
    scene()->graphicsScene()->addItem(graphicsRect);

    // création de la partie physique
    // - création du body
    b2BodyDef bodyDef;
    bodyDef.position.Set(position().x(), position().y());
    bodyDef.angle = rotation().radians();
    bodyDef.type = b2_dynamicBody;
    bodyDef.linearDamping = 0.5;
    bodyDef.angularDamping = 0.9;

    b2Body *body = scene()->physicsWorld()->CreateBody(&bodyDef);
    // - création de la forme
    b2PolygonShape shape;
    shape.SetAsBox(20, 10);
    body->CreateFixture(&shape, 1);

    // création de la box et la retourne
    Car *car = new Car(graphicsRect, body);
    return car;
}

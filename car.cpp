#include "car.h"
#include "utils.h"
#include <cmath>
#include <iostream>
#include "vector.h"
#include "rotation.h"
#include <QGraphicsRectItem>
#include <Box2D/Box2D.h>
#include "scene.h"
#include <QCoreApplication>
#include <QMessageBox>

Car::Car(QGraphicsItem *graphicsItem, b2Body *physicsBody) :
    Object(graphicsItem, physicsBody)
{
}

void Car::step(qreal throttle, qreal brakes, qreal steering)
{
    if (physicsBody())
    {
        // direction
        if (steering != 0)
        {
            steering *= 300000 * Vector(physicsBody()->GetLinearVelocity()).length();
            physicsBody()->ApplyAngularImpulse(steering);
        }

        // accélération
        float accel = 0;

        if (throttle > 0)
            accel += 1000000;
        if (brakes > 0)
           accel -= 500000;

        Vector vAccel = (Vector)(Rotation::radians(physicsBody()->GetAngle()));
        vAccel *= accel;

        physicsBody()->ApplyLinearImpulse(vAccel, physicsBody()->GetWorldCenter());
        //physicsBody()->SetLinearVelocity((Vector)physicsBody()->GetLinearVelocity() + vAccel);

        // adhérence
        //*
        Vector velocity = physicsBody()->GetLinearVelocity();
        Vector normal = physicsBody()->GetWorldVector(Vector(0,1));
        float lateralFriction = b2Dot(normal, velocity);
        normal *= lateralFriction;

        Vector impulse = -normal * physicsBody()->GetMass();
        physicsBody()->ApplyLinearImpulse( impulse, physicsBody()->GetWorldCenter() );
    }
}

Object *CarFactory::create() const
{
    using utils::toRadians;

    if (!scene())
        return nullptr;

    // création de la partie visible
    QPixmap *pixmap = new QPixmap(QCoreApplication::applicationDirPath() + "/data/carSirto.png");
    if (pixmap->isNull())
    {
       QMessageBox::information(nullptr, "Erreur", "L'image n'est pas trouvée!");
    }
    QGraphicsPixmapItem *graphics = new QGraphicsPixmapItem(*pixmap);
    graphics->setPos(position());
    graphics->setRotation(rotation().degrees());
    scene()->graphicsScene()->addItem(graphics);
    graphics->setOffset(-33,-17);

    // création de la partie physique
    // - création du body
    b2BodyDef bodyDef;
    bodyDef.position.Set(position().x(), position().y());
    bodyDef.angle = rotation().radians();
    bodyDef.type = b2_dynamicBody;
    bodyDef.linearDamping = 0.5;
    bodyDef.angularDamping = 7;

    b2Body *body = scene()->physicsWorld()->CreateBody(&bodyDef);
    // - création de la forme
    b2PolygonShape shape;
    shape.SetAsBox(33, 17);
    body->CreateFixture(&shape, 100);

    // création de la box et la retourne
    Car *car = new Car(graphics, body);
    return car;
}

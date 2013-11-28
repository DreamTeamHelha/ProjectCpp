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
    Object(graphicsItem, physicsBody),
    m_tilemap(nullptr),
    m_accelRate({0}),
    m_brakeRate({0}),
    m_maxTorque({0}),
    m_angularAccel({0}),
    m_maxLateralFriction({0})
{
}

Tilemap* Car::tilemap() const
{
    return m_tilemap;
}

void Car::setTilemap(Tilemap *tilemap)
{
    m_tilemap = tilemap;
}

void Car::step(qreal throttle, qreal brakes, qreal steering)
{
    float maxTorque = 25000000;   // prochainement propriété de la voiture
    float maxLateralFriction = 10; // ''
    float accelRate = 1000000;
    float brakeRate = 500000;
    float angularAccel = 300000;

    if (physicsBody())
    {
        // adapte le comportement du véhicule en fonction du sol où il se trouve
        if (m_tilemap)
        {
            Vector tilepos = physicsBody()->GetPosition();
            tilepos.setX( (int)(tilepos.x() / m_tilemap->tileSize()) );
            tilepos.setY( (int)(tilepos.y() / m_tilemap->tileSize()) );
            GroundType ground = m_tilemap->tile(tilepos.x(), tilepos.y());

            accelRate = m_accelRate[ground];
            brakeRate = m_brakeRate[ground];
            maxTorque = m_maxTorque[ground];
            angularAccel = m_angularAccel[ground];
            maxLateralFriction = m_maxLateralFriction[ground];
        }

        // direction
        if (steering != 0)
        {
            Vector velocity = Vector(physicsBody()->GetLinearVelocity()).normalized();
            Vector normal = Vector(physicsBody()->GetWorldVector(Vector(1,0)));
            float lateralFriction = b2Dot(normal, velocity);

            angularAccel *= steering * Vector(physicsBody()->GetLinearVelocity()).length()/100;// * lateralFriction;
            if (angularAccel > maxTorque)
            {
                angularAccel = maxTorque;
            }
            else if (angularAccel < -maxTorque)
            {
                angularAccel = -maxTorque;
            }
            physicsBody()->ApplyAngularImpulse(angularAccel);
        }

        // accélération
        {
            float accel = 0;

            if (throttle > 0)
                accel += accelRate;
            if (brakes > 0)
               accel -= brakeRate;

            Vector vAccel = (Vector)(Rotation::radians(physicsBody()->GetAngle()));
            vAccel *= accel;

            physicsBody()->ApplyLinearImpulse(vAccel, physicsBody()->GetWorldCenter());
        }

        // adhérence
        //*
        {
            Vector velocity = physicsBody()->GetLinearVelocity();
            Vector normal = physicsBody()->GetWorldVector(Vector(0,1));
            float lateralFriction = b2Dot(normal, velocity);
            if (lateralFriction > maxLateralFriction)
            {
                lateralFriction = maxLateralFriction;
            }
            else if (lateralFriction <- maxLateralFriction)
            {
                lateralFriction = -maxLateralFriction;
            }
            normal *= lateralFriction;

            Vector impulse = -normal * physicsBody()->GetMass();
            physicsBody()->ApplyLinearImpulse( impulse, physicsBody()->GetWorldCenter() );
        }
    }
}

float Car::accelRate(GroundType groundType) const
{
    if (groundType >= 0 && groundType < GroundType::_count)
    {
        return m_accelRate[groundType];
    }
    return 0;
}

float Car::brakeRate(GroundType groundType) const
{
    if (groundType >= 0 && groundType < GroundType::_count)
    {
        return m_brakeRate[groundType];
    }
    return 0;
}

float Car::maxTorque(GroundType groundType) const
{
    if (groundType >= 0 && groundType < GroundType::_count)
    {
        return m_maxTorque[groundType];
    }
    return 0;
}

float Car::angularAccel(GroundType groundType) const
{
    if (groundType >= 0 && groundType < GroundType::_count)
    {
        return m_angularAccel[groundType];
    }
    return 0;
}

float Car::maxLateralFriction(GroundType groundType) const
{
    if (groundType >= 0 && groundType < GroundType::_count)
    {
        return m_maxLateralFriction[groundType];
    }
    return 0;
}

void Car::setAccelRate(GroundType groundType, float value)
{
    if (groundType >= 0 && groundType < GroundType::_count)
    {
        m_accelRate[groundType] = value;
    }
}

void Car::setBrakeRate(GroundType groundType, float value)
{
    if (groundType >= 0 && groundType < GroundType::_count)
    {
        m_brakeRate[groundType] = value;
    }
}

void Car::setMaxTorque(GroundType groundType, float value)
{
    if (groundType >= 0 && groundType < GroundType::_count)
    {
        m_maxTorque[groundType] = value;
    }
}

void Car::setAngularAccel(GroundType groundType, float value)
{
    if (groundType >= 0 && groundType < GroundType::_count)
    {
        m_angularAccel[groundType] = value;
    }
}

void Car::setMaxLateralFriction(GroundType groundType, float value)
{
    if (groundType >= 0 && groundType < GroundType::_count)
    {
        m_maxLateralFriction[groundType] = value;
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
    b2Fixture *fixture =  body->CreateFixture(&shape, 1);

    // création de la voiture
    Car *car = new Car(graphics, body);
    fixture->SetUserData((void *)car);

    // paramétrage
    car->setTilemap(scene()->tilemap());

    car->setAccelRate(GroundType::Asphalt, 12000);
    car->setAccelRate(GroundType::Grass, 6000);
    car->setAccelRate(GroundType::Mud, 11000);

    car->setBrakeRate(GroundType::Asphalt, 5000);
    car->setBrakeRate(GroundType::Grass, 3000);
    car->setBrakeRate(GroundType::Mud, 4000);

    car->setMaxTorque(GroundType::Asphalt, 200000);
    car->setMaxTorque(GroundType::Grass, 400000);
    car->setMaxTorque(GroundType::Mud, 300000);

    car->setAngularAccel(GroundType::Asphalt, 300000);
    car->setAngularAccel(GroundType::Grass, 200000);
    car->setAngularAccel(GroundType::Mud, 100000);

    car->setMaxLateralFriction(GroundType::Asphalt, 6);
    car->setMaxLateralFriction(GroundType::Grass, 2);
    car->setMaxLateralFriction(GroundType::Mud, 3);

    return car;
}

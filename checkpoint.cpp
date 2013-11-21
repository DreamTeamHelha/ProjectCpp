#include "checkpoint.h"
#include "mathutils.h"
#include <Box2D/Box2D.h>
#include "scene.h"
#include <QCoreApplication>
#include <QMessageBox>

Checkpoint::Checkpoint(QGraphicsItem *graphicsItem, b2Body *physicsBody) :
    Object(graphicsItem, physicsBody)
{
}

Object* CheckpointFactory::create() const
{
    using mathutils::toRadians;

    if(!scene())
        return nullptr;

    // création de la partie visible
    QPixmap *pixmap = new QPixmap(QCoreApplication::applicationDirPath() + "/data/checkpoint160.png");
    if (pixmap->isNull())
    {
        QMessageBox::information(nullptr, "Erreur", "L'image n'est pas trouvée!");
    }
    QGraphicsPixmapItem *graphics = new QGraphicsPixmapItem(*pixmap);
    graphics->setPos(position());
    graphics->setRotation(rotation().degrees());
    graphics->setOffset(-80,-80);
    scene()->graphicsScene()->addItem(graphics);

    // création de la partie physique
    // - création du body
    b2BodyDef bodyDef;
    bodyDef.position.Set(position().x(), position().y());
    bodyDef.angle = rotation().radians();
    bodyDef.type = b2_kinematicBody;
    b2Body *body = scene()->physicsWorld()->CreateBody(&bodyDef);
    // - création de la forme
    b2CircleShape shape;
    shape.m_radius = 80;
    b2Fixture *fixture = body->CreateFixture(&shape, 1);
    fixture->SetSensor(true);
    fixture->SetFilterData(new b2Filter("Checkpoint"));



    // création du checkpoint et le retourne
    Checkpoint *checkpoint = new Checkpoint(graphics, body);
    return checkpoint;
}

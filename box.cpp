#include "box.h"
#include "utils.h"
#include <QGraphicsRectItem>
#include <Box2D/Box2D.h>
#include "scene.h"
#include <QCoreApplication>
#include <QMessageBox>

Box::Box(QGraphicsItem *graphicsItem, b2Body *physicsBody) :
    Object(graphicsItem, physicsBody)
{
}

Object* BoxFactory::create() const
{
    using utils::toRadians;

    if (!scene())
        return nullptr;

    // création de la partie visible
    QPixmap *pixmap = new QPixmap(QCoreApplication::applicationDirPath() + "/data/box32.png");
    if (pixmap->isNull())
    {
        QMessageBox::information(nullptr, "Erreur", "L'image n'est pas trouvée!");
    }
    QGraphicsPixmapItem *graphics = new QGraphicsPixmapItem(*pixmap);
    graphics->setPos(position());
    graphics->setRotation(rotation().degrees());
    graphics->setOffset(-16,-16);
    scene()->graphicsScene()->addItem(graphics);

    // création de la partie physique
    // - création du body
    b2BodyDef bodyDef;
    bodyDef.position.Set(position().x(), position().y());
    bodyDef.angle = rotation().radians();
    bodyDef.linearDamping = 0.8;
    bodyDef.angularDamping = 0.8;
    bodyDef.type = b2_dynamicBody;
    b2Body *body = scene()->physicsWorld()->CreateBody(&bodyDef);
    // - création de la forme
    b2PolygonShape shape;
    shape.SetAsBox(16, 16);
    body->CreateFixture(&shape, 2);

    // création de la box et la retourne
    return new Box(graphics, body);
}

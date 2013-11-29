#include "tree.h"
#include "utils.h"
#include <Box2D/Box2D.h>
#include "scene.h"
#include <QCoreApplication>
#include <QMessageBox>

Tree::Tree(QGraphicsItem *graphicsItem, b2Body *physicsBody) :
    Object(graphicsItem, physicsBody)
{
}

Object* TreeFactory::create() const
{
    using utils::toRadians;

    if(!scene())
        return nullptr;

    // création de la partie visible
    QPixmap *pixmap = new QPixmap(QCoreApplication::applicationDirPath() + "/data/tree128.png");
    if (pixmap->isNull())
    {
        QMessageBox::information(nullptr, "Erreur", "L'image n'est pas trouvée!");
    }
    QGraphicsPixmapItem *graphics = new QGraphicsPixmapItem(*pixmap);
    graphics->setPos(position());
    graphics->setRotation(rotation().degrees());
    graphics->setOffset(-64,-64);
    scene()->graphicsScene()->addItem(graphics);

    // création de la partie physique
    // - création du body
    b2BodyDef bodyDef;
    bodyDef.position.Set(position().x(), position().y());
    bodyDef.angle = rotation().radians();
    bodyDef.type = b2_staticBody;
    b2Body *body = scene()->physicsWorld()->CreateBody(&bodyDef);
    // - création de la forme
    b2CircleShape shape;
    shape.m_radius = 15;
    body->CreateFixture(&shape, 1);

    // création du tree et le retourne
    Tree *tree = new Tree(graphics, body);
    return tree;
}

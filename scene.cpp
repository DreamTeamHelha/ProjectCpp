#include "scene.h"
#include "mathutils.h"
#include <SFML/System/Time.hpp>
#include <QMessageBox>
#include <QCoreApplication>

Scene::Scene() :
    m_graphicsScene(new QGraphicsScene),
    m_physicsWorld(new b2World(Vector(0,0))),
    m_playerInput(NULL)
{
    m_car = createCar( Vector(-100,-100));
    m_objects.insert( m_car );
    m_objects.insert( createBox(1000,10,0, Vector(0,300)) );
    m_objects.insert( createBox(1000,10,0, Vector(0,-300)) );
    m_objects.insert( createBox(10,600,0, Vector(500,0)) );
    m_objects.insert( createBox(10,600,0, Vector(-500,0)) );
    m_objects.insert( createBox(20,40,1, Vector(0,-150), Rotation::degrees(45) ) );
    m_objects.insert( createBox(10,10,1, Vector(0,-105)));
    m_objects.insert( createBox(10,50,0.5, Vector(10,-250), Rotation::degrees(-20)) );
    m_objects.insert( createBox(50,50,100, Vector(-10,-200)) );
    m_objects.insert( createBox32(Vector(0,100)));

    BoxFactory boxFactory;
    boxFactory.setScene(this);

    boxFactory.setPosition(Vector(-20, -20));
    boxFactory.setRotation(Rotation::degrees(45));
    m_objects.insert( boxFactory.create() );
    boxFactory.setPosition(Vector(20,-20));
    boxFactory.setRotation(Rotation());
    m_objects.insert( boxFactory.create() );
}

Scene::~Scene()
{
    for (Object *object : m_objects)
    {
        delete object;
    }
    m_objects.clear();
    delete m_graphicsScene;
}

QGraphicsScene *Scene::graphicsScene() const
{
    return m_graphicsScene;
}

b2World *Scene::physicsWorld() const
{
    return m_physicsWorld;
}

bool Scene::addObject(Object *object)
{
    if (!object)
        return false;

    /*
    auto ret = m_objects.insert(object);
    if (ret->second) // ajout au set réussi
    {
        // ajout du composant graphique
        if (object->graphicsItem())
            m_graphicsScene->addItem(object->graphicsItem());
    }
    //*/
    return true;
}

const PlayerInput *Scene::playerInput() const
{
    return m_playerInput;
}

void Scene::setPlayerInput(const PlayerInput *playerInput)
{
    m_playerInput = playerInput;
}

void Scene::update()
{
    /// Commande le véhicule
    if (m_playerInput)
    {
        m_car->step(m_playerInput->throttle(), m_playerInput->brakes(), m_playerInput->turnRight()-m_playerInput->turnLeft());
    }

    /// Mise à jour de la physique
    m_physicsWorld->Step(sf::seconds(1.f/60.f).asSeconds(), 8, 3);

    /// Mise à jour de tous les objets.
    for (Object *object : m_objects)
    {
        object->update();
    }
}

Box* Scene::createBox(qreal width, qreal height, qreal mass, const Vector &position, const Rotation &rotation)
{
    using mathutils::toRadians;

    // création de la partie visible
    QGraphicsRectItem *graphicsRect = new QGraphicsRectItem(-width/2, -height/2, width, height);
    graphicsRect->setPos(position);
    graphicsRect->setRotation(rotation.degrees());
    m_graphicsScene->addItem(graphicsRect);

    // création de la partie physique
    // - création du body
    b2BodyDef bodyDef;
    bodyDef.position.Set(position.x(), position.y());
    bodyDef.angle = rotation.radians();
    bodyDef.linearDamping = 0.8;
    bodyDef.angularDamping = 0.8;
    if (mass > 0)
    {
        bodyDef.type = b2_dynamicBody;
    }
    else
    {
        bodyDef.type = b2_staticBody;
    }
    b2Body *body = m_physicsWorld->CreateBody(&bodyDef);
    // - création de la forme
    b2PolygonShape shape;
    shape.SetAsBox(width/2, height/2);
    body->CreateFixture(&shape, 1);

    // création de la box et la retourne
    Box *box = new Box(graphicsRect, body);
    return box;
}

Box *Scene::createBox32(const Vector& position, const Rotation& rotation)
{
    using mathutils::toRadians;

    // création de la partie visible
    QPixmap *pixmap = new QPixmap(QCoreApplication::applicationDirPath() + "/data/box32.png");
    if (pixmap->isNull())
    {
        QMessageBox::information(nullptr, "Erreur", "L'image n'est pas trouvée!");
    }
    QGraphicsPixmapItem *graphics = new QGraphicsPixmapItem(*pixmap);
    graphics->setPos(position);
    graphics->setRotation(rotation.degrees());
    m_graphicsScene->addItem(graphics);
    graphics->setOffset(-16,-16);

    // création de la partie physique
    // - création du body
    b2BodyDef bodyDef;
    bodyDef.position.Set(position.x(), position.y());
    bodyDef.angle = rotation.radians();
    bodyDef.linearDamping = 0.8;
    bodyDef.angularDamping = 0.8;
    bodyDef.type = b2_dynamicBody;
    b2Body *body = m_physicsWorld->CreateBody(&bodyDef);
    // - création de la forme
    b2PolygonShape shape;
    shape.SetAsBox(16, 16);
    body->CreateFixture(&shape, 1);

    // création de la box et la retourne
    Box *box = new Box(graphics, body);
    return box;
}


Car* Scene::createCar(const Vector &position, const Rotation &rotation)
{
    using mathutils::toRadians;

    // création de la partie visible
    QGraphicsRectItem *graphicsRect = new QGraphicsRectItem(-20, -10, 40, 20);
    graphicsRect->setPos(position);
    graphicsRect->setRotation(rotation.degrees());
    m_graphicsScene->addItem(graphicsRect);

    // création de la partie physique
    // - création du body
    b2BodyDef bodyDef;
    bodyDef.position.Set(position.x(), position.y());
    bodyDef.angle = rotation.radians();
    bodyDef.type = b2_dynamicBody;
    bodyDef.linearDamping = 0.5;
    bodyDef.angularDamping = 0.9;

    b2Body *body = m_physicsWorld->CreateBody(&bodyDef);
    // - création de la forme
    b2PolygonShape shape;
    shape.SetAsBox(20, 10);
    body->CreateFixture(&shape, 1);

    // création de la box et la retourne
    Car *car = new Car(graphicsRect, body);
    return car;
}

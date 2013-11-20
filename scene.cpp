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
    // création de la voiture
    CarFactory carFactory;
    carFactory.setScene(this);

    carFactory.setPosition(Vector(-100, -100));
    m_car = dynamic_cast<Car*>( carFactory.create() );
    m_objects.insert(m_car);

    // création de deux boites
    BoxFactory boxFactory;
    boxFactory.setScene(this);

    boxFactory.setPosition(Vector(-20, -20));
    boxFactory.setRotation(Rotation::degrees(45));
    m_objects.insert( boxFactory.create() );
    boxFactory.setPosition(Vector(20,-20));
    boxFactory.setRotation(Rotation());
    m_objects.insert( boxFactory.create() );

    // création d'un arbre
    TreeFactory treeFactory;
    treeFactory.setScene(this);

    treeFactory.setPosition(Vector(-50,-50));
    m_objects.insert(treeFactory.create());
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

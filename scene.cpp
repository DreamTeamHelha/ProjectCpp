 #include "scene.h"
#include "mathutils.h"
#include <SFML/System/Time.hpp>
#include <QMessageBox>
#include <QCoreApplication>
#include <QGraphicsItem>

Scene::Scene(Tilemap *tilemap) :
    m_graphicsScene(new QGraphicsScene),
    m_physicsWorld(new b2World(Vector(0,0))),
    m_playerInput(nullptr),
    m_tilemap(tilemap)

{
    //Chargement de la map
    loadMap();
    // création de la voiture
    CarFactory carFactory;
    carFactory.setScene(this);

    carFactory.setPosition(Vector(2000,2000));
    m_car = dynamic_cast<Car*>( carFactory.create() );
    m_objects.insert(m_car);

  /*  // création de deux boites
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
    m_objects.insert(treeFactory.create());*/
}

Scene::~Scene()
{
    for (Object *object : m_objects)
    {
        delete object;
    }
    m_objects.clear();
    delete m_graphicsScene;
    delete m_tilemap;
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

const Tilemap *Scene::tilemap() const
{
    return m_tilemap;
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

void Scene::loadMap()
{
    QPixmap *grassTile = new QPixmap(QCoreApplication::applicationDirPath() + "/data/tiles/GrassTile.png");
    if (grassTile->isNull())
    {
        QMessageBox::information(nullptr, "Erreur", "L'image n'est pas trouvée!");
    }

    QPixmap *roadTile = new QPixmap(QCoreApplication::applicationDirPath() + "/data/tiles/RoadTile.png");
    if (roadTile->isNull())
    {
        QMessageBox::information(nullptr, "Erreur", "L'image n'est pas trouvée!");
    }

    for(int x=0;x<m_tilemap->width();x++)
    {
        for(int y=0;y<m_tilemap->height();y++)
        {
            QGraphicsPixmapItem *item;
            switch(m_tilemap->tile(y,x))
            {
            case GroundType::Asphalt :  item = new QGraphicsPixmapItem(*roadTile);
                      break;
            default : item = new QGraphicsPixmapItem(*grassTile);
            }
            item->setPos(x*32,y*32);
            this->graphicsScene()->addItem(item);
        }
    }

}

Vector Scene::calcViewPoint()
{
    Vector viewPoint;
    if (m_car)
    {
        viewPoint = Vector(m_car->physicsBody()->GetPosition());
    }
    return viewPoint;
}

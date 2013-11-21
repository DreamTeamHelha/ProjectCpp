 #include "scene.h"
#include "mathutils.h"
#include <SFML/System/Time.hpp>
#include <QMessageBox>
#include <QCoreApplication>
#include <QGraphicsItem>
#include "objectfactories.h"
#include "tilemaploader.h"
#include "vector.h"

Scene::Scene() :
    m_graphicsScene(new QGraphicsScene),
    m_physicsWorld(new b2World(Vector(0,0))),
    m_playerInput(nullptr),
    m_tilemap(nullptr),
    m_loaded(false)

{
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

bool Scene::load(const QString &levelName)
{
    //Permet de vérifier que la scène ne soit pas chargée plusieurs fois
    if(m_loaded)
    {
        return false;
    }

    m_tilemap= TilemapLoader::load(QCoreApplication::applicationDirPath()+"/data/tracks/"+levelName+".png");
    //Chargement de la map
    if(!loadMap())
    {
        return false;
    }

    // récupération des factories
    ObjectFactory *factory = ObjectFactories::getFactory("Car");
    if (!factory)
    {
        return false;
    }
    else
    {
        factory->setScene(this);

        factory->setPosition(Vector(2000,2000));
        m_car = dynamic_cast<Car*>( factory->create() );
        addObject(m_car);
    }

    m_loaded=true;
    return true;
}

bool Scene::addObject(Object *object)
{
    if (!object)
        return false;

    m_objects.insert(object);
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

bool Scene::loadMap()
{
    QPixmap *grassTile = new QPixmap(QCoreApplication::applicationDirPath() + "/data/tiles/GrassTile.png");
    if (grassTile->isNull())
    {
       return false;
    }

    QPixmap *roadTile = new QPixmap(QCoreApplication::applicationDirPath() + "/data/tiles/RoadTile.png");
    if (roadTile->isNull())
    {
        return false;
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
    Vector v1;
    Vector v2(m_tilemap->width()*32,0.f);
    Vector v3(0.f,m_tilemap->height()*32);
    Vector v4(m_tilemap->width()*32,m_tilemap->height()*32);


    b2BodyDef bodyDef;
    bodyDef.type = b2_staticBody;
    b2Body *body = physicsWorld()->CreateBody(&bodyDef);
    b2EdgeShape lineUp;
    lineUp.Set(v1,v2);
    body->CreateFixture(&lineUp,1);
    b2EdgeShape lineLeft;
    lineLeft.Set(v1,v3);
    body->CreateFixture(&lineLeft,1);
    b2EdgeShape lineRight;
    lineRight.Set(v2,v4);
    body->CreateFixture(&lineRight,1);
    b2EdgeShape lineBottom;
    lineBottom.Set(v3,v4);
    body->CreateFixture(&lineBottom,1);


    return true;

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

bool Scene::loaded() const
{
    return m_loaded;
}

#pragma once

#include <QGraphicsScene>
#include "playerinput.h"
#include "box.h"
#include "car.h"
#include "object.h"
#include <Box2D/Box2D.h>
#include <set>
#include "vector.h"
#include "rotation.h"
#include "tree.h"
#include "tilemap.h"
#include "objectfactory.h"
#include "checkpointlistener.h"
#include <QTime>
#include "view.h"

class Scene
{
public:

    Scene();
    virtual ~Scene();

    ///
    /// Getters
    ///
    QGraphicsScene *graphicsScene() const;
    b2World        *physicsWorld () const;

    ///
    /// Charge la scène
    ///
    bool load(const QString& levelName, const QString& carClassName);

    ///
    /// Ajoute un objet à la scène
    ///
    bool addObject(Object* object);

    ///
    /// Crée la voiture du joueur, et la retourne.
    /// Si la voiture du joueur à déjà été créée, elle est simplement retournée.
    /// Cette fonction prend en paramètre la position de création de la voiture,
    /// la rotation initiale, et l'instance d'ObjectFactory servant à la création du véhicule.
    ///
    Car *createPlayerCar(const Vector& position, const Rotation& rotation, ObjectFactory *carFactory);

    ///
    /// Permet l'assignation et la récupération du playerInput utilisé pour commander le véhicule
    ///
    const PlayerInput *playerInput() const;
    void  setPlayerInput(const PlayerInput *playerInput);

    ///
    /// Met à jour la logique de jeu
    ///
    void update();

    ///
    ///Permet la récupération de la tilemap
    ///
    Tilemap *tilemap() const;

    ///
    /// Calcule le point de vue de la caméra
    ///
    View calcViewPoint();

    ///
    ///Permet de récupérer l'état de chargement de la scène
    ///
    bool loaded()const;

    ///
    ///Permet de dire si la course est finie ou non
    ///
    bool isFinished() const;

    ///
    /// Permet de démarrer la partie
    ///
    void start();

    ///
    /// Permet de récuperer le temps de la scène
    ///
    const QTime & time()const;

    ///
    ///
    ///
    const CheckpointListener * checkpointListener() const;

    void setTime(int);


private:

    QGraphicsScene      *m_graphicsScene;
    b2World             *m_physicsWorld;
    const PlayerInput   *m_playerInput;
    Car                 *m_car;
    std::set<Object*>    m_objects;
    Tilemap             *m_tilemap;
    bool                 m_loaded;
    CheckpointListener  *m_checkpointListener;
    QTime                m_time;

    ///
    /// Permet de charger la map
    ///
    bool loadMap();

};

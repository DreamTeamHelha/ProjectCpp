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
    bool load(const QString & levelName);

    ///
    /// Ajoute un objet à la scène
    ///
    bool addObject(Object* object);

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
    const Tilemap *tilemap() const;

    ///
    /// Calcule le point de vue de la caméra
    ///
    Vector calcViewPoint();

    ///
    ///Permet de récupérer l'état de chargement de la scène
    ///
    bool loaded()const;

private:

    QGraphicsScene      *m_graphicsScene;
    b2World             *m_physicsWorld;
    const PlayerInput   *m_playerInput;
    Car                 *m_car;
    std::set<Object*>    m_objects;
    Tilemap             *m_tilemap;
    bool                 m_loaded;

    ///
    /// Permet de charger la map
    ///
    bool loadMap();

};

#pragma once

#include <QGraphicsScene>
#include "playerinput.h"
#include "box.h"
#include "car.h"
#include "object.h"
#include <Box2D/Box2D.h>
#include <vector>
#include "vector.h"
#include "rotation.h"

class Scene
{
public:

    Scene();
    virtual ~Scene();

    QGraphicsScene  *graphicsScene() const;
    const b2World *physicsWorld() const;

    ///
    /// Permet l'assignation et la récupération du playerInput utilisé pour commander le véhicule
    ///
    const PlayerInput *playerInput() const;
    void setPlayerInput(const PlayerInput *playerInput);

    ///
    /// Met à jour la logique de jeu
    ///
    void update();

    ///
    /// Méthodes provisoires (tests)
    ///
    Box *createBox(qreal width, qreal height, qreal mass, const Vector& position=Vector(), const Rotation& rotation=Rotation());
    Car *createCar(const Vector& position=Vector(), const Rotation& rotation=Rotation());
    Box *createBox32(const Vector& position, const Rotation& rotation = Rotation());

private:

    QGraphicsScene      *m_graphicsScene;
    b2World              m_physicsWorld;
    const PlayerInput   *m_playerInput;
    Car                 *m_car;
    std::vector<Object*> m_objects;
};

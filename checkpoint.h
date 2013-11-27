#pragma once
#include "object.h"
#include "objectfactory.h"

class Checkpoint : public Object
{
private:
    bool m_touched;
public:
    Checkpoint(QGraphicsItem *graphicsItem, b2Body *physicsBody);

    ///Permet de spécifier au Checkpoint qu'il est touché
    void touch();

    ///Permet de savoir si le Checkpoint a déjà été touché
    bool touched();

};

class CheckpointFactory : public ObjectFactory
{
public:

    ///Crée un objet 'Checkpoint' et le retourne
    Object *create() const;
};

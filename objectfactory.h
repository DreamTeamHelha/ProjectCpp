#pragma once

#include "object.h"
#include "vector.h"
#include "rotation.h"

class Scene;

///
/// Classe de base pour les créateurs d'objets
///
class ObjectFactory
{
protected:

    ObjectFactory();

public:

    virtual ~ObjectFactory() = default;

    ///
    /// Crée un nouvel objet.
    /// Doit être réimplémentée dans les sous-classes.
    ///
    virtual Object *create() const = 0;

    ///
    /// Position à laquelle le prochain objet sera créé
    ///
    const Vector & position    () const;
    void           setPosition (const Vector& position);

    ///
    /// Rotation avec laquelle le prochain objet sera créé
    ///
    const Rotation &rotation    () const;
    void            setRotation (const Rotation& rotation);

    ///
    /// Scène dans laquelle le prochain objet sera créé
    ///
    Scene         *scene() const;
    void           setScene(Scene *scene);

private:

    Vector      m_position;
    Rotation    m_rotation;
    Scene      *m_scene;
};


//////////////////////////////////////////////
/// Implémentation
///
inline ObjectFactory::ObjectFactory() :
    m_scene(nullptr)
{}

inline const Vector& ObjectFactory::position() const
{
    return m_position;
}

inline void ObjectFactory::setPosition(const Vector &position)
{
    m_position = position;
}

inline const Rotation& ObjectFactory::rotation() const
{
    return m_rotation;
}

inline void ObjectFactory::setRotation(const Rotation &rotation)
{
    m_rotation = rotation;
}

inline Scene *ObjectFactory::scene() const
{
    return m_scene;
}

inline void ObjectFactory::setScene(Scene *scene)
{
    m_scene = scene;
}

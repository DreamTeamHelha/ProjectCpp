#pragma once

#include <QGraphicsItem>
#include <Box2D/Box2D.h>

///
/// Classe de base pour tous les objets de la scène
///
class Object
{
public:

    ///
    /// Construit un objet d'une scène.
    /// - graphicsItem est le composant visible de l'objet, destiné à l'affichage.
    /// - physicsBody est le composant physique de l'objet, servant aux calculs de collision.
    /// La libération de la mémoire des deux composants n'est pas prise en charge par la classe Object.
    ///
    Object(QGraphicsItem *graphicsItem, b2Body *physicsBody);
    virtual ~Object();

    ///
    /// Getters
    ///
    QGraphicsItem   *graphicsItem() const;
    b2Body          *physicsBody() const;

    ///
    /// Appellée après le step physique.
    /// Fait coincider la position et la rotation du graphicsItem avec le physicsBody.
    /// Cette méthode peut être réimplémentée par les sous classes devant effectuer certaines choses après que le
    /// déplacement des objets (ne pas oublier l'appel à Object::update dans la réimplémentation ).
    ///
    virtual void update();

private:

    QGraphicsItem   *m_graphicsItem;
    b2Body          *m_physicsBody;
};

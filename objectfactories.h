#pragma once

#include "objectfactory.h"
#include <QMap>
#include <QString>

///
/// Classe contenant tous les constructeurs d'objets du jeu
///
class ObjectFactories
{
public:

    ObjectFactories() = delete;
    ~ObjectFactories() = delete;

    ///
    /// Cette fonction est appellée au lancement du programme.
    /// Son implémentation crée un constructeur pour chaque type d'objet jouable.
    ///
    static void initialize();

    ///
    /// Retourne la factory portant le nom
    ///
    static ObjectFactory *getFactory(const QString& factoryName);

    ///
    /// Crée une factory de type T, l'ajoute à l'ensemble sous le nom factoryName, et la retourne.
    /// Si une factory de ce nom existe déjà, elle sera directement retournée et ne sera pas recréée.
    ///
    template <typename T>
    static ObjectFactory *createFactory(const QString& factoryName);

    ///
    /// Cette fonction est appellée à la fin du programme.
    /// Elle détruit tous les constructeurs d'objets ajoutés par finalize.
    ///
    static void finalize();

private:

    static QMap<QString, ObjectFactory*> m_factories;
};

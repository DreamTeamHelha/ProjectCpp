#pragma once

#include "scene.h"
#include <QString>

using namespace std;

///
/// Classe servant au chargement des objets d'une scène depuis un fichier json
///
class ObjectLoader
{
public:

    ObjectLoader(Scene *scene, const QString& carClassName);

    ///
    /// Scène dans laquelle les objets doivent être créés.
    ///
    Scene *scene() const;

    ///
    /// Nom de la classe de la voiture du joueur
    ///
    const QString& carClassName() const;

    ///
    /// Charge les objets et les ajoute à la scène.
    ///
    bool load(const QString& filename);

private:

    Scene  *m_scene;
    QString m_carClassName;
};

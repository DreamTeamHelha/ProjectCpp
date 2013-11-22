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

    ObjectLoader();

    ///
    /// Scène dans laquelle les objets doivent être créés.
    ///
    Scene *scene() const;
    void setScene(Scene*);

    ///
    /// Nom de la classe de la voiture du joueur
    ///
    const QString& carClassName() const;
    void setCarClassName(const QString& carClassName);

    ///
    /// Charge les objets et les ajoute à la scène.
    ///
    bool load(const QString& filename);

private:

    Scene  *m_scene;
    QString m_carClassName;
};

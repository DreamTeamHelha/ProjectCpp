#pragma once

#include "string.h"
#include <QJsonDocument>
#include <QFile>
#include <QtDebug>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>
#include <QDir>
#include "scene.h"

using namespace std;

class ObjectLoader
{
private:

    Scene *m_scene;

public:

    ObjectLoader();

    Scene *scene() const;
    void setScene(Scene*);

    bool load(const QString& filename);
};

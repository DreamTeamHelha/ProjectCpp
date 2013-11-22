#include "objectloader.h"
#include "objectfactories.h"
#include <iostream>
#include "rotation.h"
#include "vector.h"
#include <cstdlib>
#include <QJsonDocument>
#include <QJsonObject>
#include <QFile>
#include <QJsonArray>

using namespace::std;

ObjectLoader::ObjectLoader(Scene *scene, const QString &carClassName) :
    m_scene(scene),
    m_carClassName(carClassName)
{
}

Scene *ObjectLoader::scene()const
{
    return m_scene;
}

const QString& ObjectLoader::carClassName() const
{
    return m_carClassName;
}

bool ObjectLoader::load(const QString& filename)
{
    if (!m_scene)
        return false;

    QString val;
    QJsonObject item;
    QString className;
    QFile file(filename);

    file.open(QIODevice::ReadOnly | QIODevice::Text);
    if(!file.isOpen())
    {
        return false;
    }

    val = file.readAll();
    file.close();

    QJsonDocument document = QJsonDocument::fromJson(val.toUtf8());
    if(document.isEmpty())
    {
        return false;
    }

    QJsonArray root = document.array();
    for(int i=0;i<root.count();i++)
    {
        item =root[i].toObject();
        className=item["class"].toString();
        float x=item["x"].toDouble();
        float y=item["y"].toDouble();
        Rotation rotation=Rotation::degrees(item["rot"].toDouble());
        Vector position(x,y);

        ObjectFactory *objectFactory(nullptr);

        /// Cas spécial : l'objet playerStart définis la position et la rotation de la voiture du joueur.
        if (className == "PlayerStart")
        {
           objectFactory = ObjectFactories::getFactory(m_carClassName);
           if (objectFactory)
           {
               m_scene->createPlayerCar(position, rotation, objectFactory);
           }
        }
        /// Sinon on recherche la factory et on crée un objet avec.
        else
        {
            objectFactory = ObjectFactories::getFactory(className);
            if(objectFactory)
            {
                objectFactory->setScene(m_scene);
                objectFactory->setPosition(position);
                objectFactory->setRotation(rotation);
                Object *obj=objectFactory->create();
                if(obj)
                {
                   m_scene->addObject(obj);
                }
            }
         }
    }
    return true;
}

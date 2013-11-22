#include "objectloader.h"
#include "objectfactories.h"
#include <iostream>
#include "rotation.h"
#include "vector.h"
#include <cstdlib>
using namespace::std;

ObjectLoader::ObjectLoader()
{
}

Scene *ObjectLoader::scene()const
{
    return m_scene;
}

void ObjectLoader::setScene(Scene *scene)
{
    m_scene=scene;
}

bool ObjectLoader::load(const QString& filename)
{
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

        ObjectFactory *objectFactory = ObjectFactories::getFactory(className);
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
    return true;
}

#include "objectfactories.h"

#include "car.h"
#include "box.h"
#include "tree.h"
#include "checkpoint.h"

QMap<QString, ObjectFactory*> ObjectFactories::m_factories;

void ObjectFactories::initialize()
{
    createFactory<CarFactory>("Car");
    createFactory<BoxFactory>("Box");
    createFactory<TreeFactory>("Tree");
    createFactory<CheckpointFactory>("Checkpoint");

}

ObjectFactory *ObjectFactories::getFactory(const QString &factoryName)
{
    QMap<QString, ObjectFactory*>::Iterator it = m_factories.find(factoryName);
    if (it == m_factories.end())
    {
        return nullptr;
    }
    else
    {
        return it.value();
    }
}

template <typename T>
ObjectFactory *ObjectFactories::createFactory(const QString &factoryName)
{
    ObjectFactory *factory = getFactory(factoryName);
    if (!factory)
    {
        factory = new T();
        m_factories.insert(factoryName, factory);
    }
    return factory;
}

void ObjectFactories::finalize()
{
    for (ObjectFactory* factory : m_factories)
    {
        delete factory;
    }
    m_factories.clear();
}

#pragma once
#include <Box2D/Box2D.h>
#include <scene.h>

class CheckpointListener : public b2ContactListener
{
private:
    Scene *m_scene;
public:
    CheckpointListener(Scene *scene);
    void BeginContact (b2Contact *contact);
};


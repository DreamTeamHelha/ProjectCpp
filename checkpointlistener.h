#pragma once
#include <Box2D/Box2D.h>

class CheckpointListener : public b2ContactListener
{
public:
    CheckpointListener();
    void BeginContact (b2Contact *contact);
};


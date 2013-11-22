#pragma once
#include <Box2D/Box2D.h>


class CheckpointListener : public b2ContactListener
{
private:
    int m_checkpointRemaining;
public:
    CheckpointListener();
    void BeginContact (b2Contact *contact);
    void setCheckpointNumber(int number);
    bool hasCheckpointRemaining();
};


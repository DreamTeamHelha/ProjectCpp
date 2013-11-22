#include "checkpointlistener.h"
#include <QMessageBox>
#include "checkpoint.h"

CheckpointListener::CheckpointListener():
    m_checkpointRemaining(-1)
{
}

void CheckpointListener::BeginContact (b2Contact *contact)
{
    void *data = contact->GetFixtureB()->GetUserData();
    if(data)
    {
        Checkpoint *checkpoint = (Checkpoint *)(contact->GetFixtureB()->GetUserData());
        if(checkpoint)
        {
            if(!checkpoint->touched())
            {
                checkpoint->touch();
                m_checkpointRemaining--;
            }
        }
    }
}

void CheckpointListener::setCheckpointNumber(int number)
{
    if(m_checkpointRemaining == -1)
        m_checkpointRemaining = number;
}

bool CheckpointListener::hasCheckpointRemaining()
{
    return m_checkpointRemaining >0;
}

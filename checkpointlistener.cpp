#include "checkpointlistener.h"
#include <QMessageBox>
#include "checkpoint.h"
#include "car.h"

CheckpointListener::CheckpointListener():
    m_checkpointRemaining(-1)
{
}

void CheckpointListener::BeginContact (b2Contact *contact)
{
    void *dataCar = contact->GetFixtureA()->GetUserData();
    if(dataCar)
    {
        Car *car = (Car *)(contact->GetFixtureA()->GetUserData());
        if(car)
        {

            void *dataCheckpoint = contact->GetFixtureB()->GetUserData();
            if(dataCheckpoint)
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

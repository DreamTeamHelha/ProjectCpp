#pragma once
#include <Box2D/Box2D.h>


class CheckpointListener : public b2ContactListener
{
private:
    int m_checkpointRemaining;
public:
    CheckpointListener();

    ///Méthode appelée au début du contact entre 2 objets
    void BeginContact (b2Contact *contact);

    ///Permet de fixer le nombre de checkpoint à passer pour finir la course
    void setCheckpointNumber(int number);

    ///Renvoie true s'il reste encore des checkpoints à passer pour finir la course
    bool hasCheckpointRemaining();

    ///Renvoie le nombre de checkpoint devant encore être passés pour finir la course
    const int  checkpointRemaining() const;
};


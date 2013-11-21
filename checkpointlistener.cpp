#include "checkpointlistener.h"
#include <QMessageBox>

CheckpointListener::CheckpointListener()
{
}
void CheckpointListener::BeginContact (b2Contact *contact)
{
    QMessageBox::information(nullptr,"Réussite", contact->GetFixtureB()->GetUserData());
    QMessageBox::information(nullptr, "Réussite", "Collision");
}

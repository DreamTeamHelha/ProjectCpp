#include "checkpointlistener.h"
#include <QMessageBox>

CheckpointListener::CheckpointListener(Scene *scene):m_scene(scene)
{
}
void CheckpointListener::BeginContact (b2Contact *contact)
{
    QMessageBox::information(nullptr, "Réussite", "Collision");
}

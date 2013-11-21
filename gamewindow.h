#pragma once

#include <QDialog>
#include "scene.h"
#include "playerinput.h"

namespace Ui {
class GameWindow;
}

///
/// Fenêtre de jeu
/// Contient seulement une vue, et transmet les événements du clavier à une instance de PlayerInput.
///
class GameWindow : public QDialog
{
    Q_OBJECT
    
public:

    explicit GameWindow(QWidget *parent = 0);
    ~GameWindow();

    ///
    /// Autorise l'accès et le changement de la scène affichée par la fenêtre.
    ///
    Scene *scene() const;
    void setScene(Scene *scene);

    ///
    /// Retourne l'instance de PlayerInput associée à cette fenêtre.
    ///
    const PlayerInput& playerInput() const;

protected:

    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    void timerEvent(QTimerEvent *event);

private:

    Scene           *m_scene;
    PlayerInput     m_playerInput;
    Ui::GameWindow  *ui;
};

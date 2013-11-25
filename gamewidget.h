#pragma once

#include <QGraphicsView>
#include <scene.h>
#include <playerinput.h>
#include <QString>

///
/// Widget servant à l'affichage et à la gestion d'un niveau.
///
class GameWidget : public QGraphicsView
{
public:

    ///
    /// Crée un widget pour la scène passée en paramètre.
    /// La scène doit être chargée avant l'appel de ce constructeur,
    /// et sera détruite avec le GameWidget.
    ///
    GameWidget(Scene *scene, QWidget *parent=nullptr);
    ~GameWidget();

    ///
    /// Getters
    ///
          Scene       * scene()       const;
    const PlayerInput & playerInput() const;

protected:

    ///
    /// Gère les événements du clavier
    ///
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    ///
    /// Met à jour la scène tous les 1/60eme de seconde.
    ///
    void timerEvent(QTimerEvent *event);

private:

    QString     m_levelName;
    Scene      *m_scene;
    PlayerInput m_playerInput;
};

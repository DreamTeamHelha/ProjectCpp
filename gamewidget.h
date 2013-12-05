#pragma once

#include <QGraphicsView>
#include <scene.h>
#include <playerinput.h>
#include <QString>
#include <QLabel>

///
/// Widget servant à l'affichage et à la gestion d'un niveau.
///
class GameWidget : public QGraphicsView
{
    Q_OBJECT
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
    bool paused()       const;

    void pause();
    void setPaused(bool paused);

signals:

    void gamePaused(QTime);
    void showScore (const QString&);

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

    QString      m_levelName;
    Scene       *m_scene;
    PlayerInput  m_playerInput;
    QLabel       m_timeLabel;
    QLabel       m_checkpointRemainingLabel;
    bool         m_paused;
    float        m_cameraScale;
    unsigned     m_frameCount;
};

#include "gamewidget.h"
#include <SFML/System/Time.hpp>
#include <QMessageBox>
#include <QKeyEvent>


GameWidget::GameWidget(Scene *scene, QWidget *parent) :
    QGraphicsView(parent),
    m_scene(scene),
    m_timeLabel("Test")
{
    if (!scene)
    {
        QMessageBox::information(nullptr, "Erreur (GameWidget)", "Aucune scène a afficher!", 0);
    }
    else if (!scene->loaded())
    {
        QMessageBox::information(nullptr, "Erreur (GameWidget)", "Le niveau n'a pas été chargé!", 0);
    }
    else
    {
        /*
        m_timeLabel.show();
        m_timeLabel.setGeometry(0,0,100,100);
        // prépare la scène pour l'affichage
        */

        this->setScene(scene->graphicsScene());
        this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

        // réglages du clavier
        grabKeyboard();
        scene->setPlayerInput(&m_playerInput);

        // démarrage du timer de rafraichissement du jeu
        startTimer(sf::seconds(1/60.f).asMilliseconds());

        //Démarrage du timer de temps
        scene->start();
    }
}

GameWidget::~GameWidget()
{
    if (m_scene)
        delete m_scene;
}

Scene *GameWidget::scene() const
{
    return m_scene;
}

const PlayerInput& GameWidget::playerInput() const
{
    return m_playerInput;
}


void GameWidget::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())
    {
    case Qt::Key_Up:
        m_playerInput.setThrottle(true);
        break;

    case Qt::Key_Down:
        m_playerInput.setBrakes(true);
        break;

    case Qt::Key_Left:
        m_playerInput.setTurnLeft(true);
        break;

    case Qt::Key_Right:
        m_playerInput.setTurnRight(true);
        break;

    case Qt::Key_Escape:
        m_playerInput.setPause(true);
        break;

    default:
         QGraphicsView::keyPressEvent(event);
    }
}

void GameWidget::keyReleaseEvent(QKeyEvent *event)
{
    switch (event->key())
    {
    case Qt::Key_Up:
        m_playerInput.setThrottle(false);
        break;

    case Qt::Key_Down:
        m_playerInput.setBrakes(false);
        break;

    case Qt::Key_Left:
        m_playerInput.setTurnLeft(false);
        break;

    case Qt::Key_Right:
        m_playerInput.setTurnRight(false);
        break;

    case Qt::Key_Escape:
        m_playerInput.setPause(false);
        break;

    default:
         QGraphicsView::keyReleaseEvent(event);
    }
}

void GameWidget::timerEvent(QTimerEvent *)
{
    if (m_scene)
    {

        if(m_scene->isFinished())
        {
          //QMessageBox::information(nullptr, "Réussite", "Fin de course!");
        }
        else
        {
            /// mise à jour de la scène
            m_scene->update();

            /// mise à jour de la caméra
            View view = m_scene->calcViewPoint();
            centerOn(view.position());
            scale(view.zoom(), view.zoom());

            /// mise à jour du compteur
            QString timeString;
            timeString.number(m_scene->time().elapsed()/1000);
            m_timeLabel.setText(timeString);
        }
    }
}

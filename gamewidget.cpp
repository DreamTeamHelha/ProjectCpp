#include "gamewidget.h"
#include <SFML/System/Time.hpp>
#include <QMessageBox>
#include <QKeyEvent>
#include "utils.h"
#include <iostream>
#include "mainwindow.h"
#include "pausemenu.h"


GameWidget::GameWidget(Scene *scene, QWidget *parent) :
    QGraphicsView(parent),
    m_scene(scene),
    m_timeLabel(this),
    m_checkpointRemainingLabel(this),
    m_paused(false),
    m_cameraScale(1.f),
    m_frameCount(0),
    m_timeBeforeBeginRemainingLabel(this)
{
    m_preStartTimer = new PreStartTimer(this);
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
        this->setCursor(Qt::BlankCursor);

        //Placement du label du timer
        m_timeLabel.setGeometry(0,0,500,50);
        m_timeLabel.setStyleSheet("color: rgb(255, 47, 28);font: 24pt \"MS Shell Dlg 2\";");

        //Placement du label du nombre de checkpoints restants
        m_checkpointRemainingLabel.setGeometry(parent->width()-220,0,220,50);
        m_checkpointRemainingLabel.setStyleSheet("color: rgb(255, 47, 28);font: 14pt \"MS Shell Dlg 2\";");

        //Placement du label du timer d'avant jeu
        m_timeBeforeBeginRemainingLabel.setGeometry(350,250,100,100);
        m_timeBeforeBeginRemainingLabel.setStyleSheet("color: rgb(255, 47, 28);font: 95pt \"MS Shell Dlg 2\";");

        // prépare la scène pour l'affichage
        this->setScene(scene->graphicsScene());
        this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

        // réglages du clavier
        grabKeyboard();
        scene->setPlayerInput(&m_playerInput);

        // démarrage du timer de rafraichissement du jeu
        startTimer(sf::seconds(1/60.f).asMilliseconds());

        View view = m_scene->calcViewPoint();
        centerOn(view.position());

        connect(m_preStartTimer,SIGNAL(endTimer()),this,SLOT(startGame()));
    }
}

GameWidget::~GameWidget()
{
    std::cout << "GameWidget deleted" << std::endl;
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

bool GameWidget::paused()const
{
    return m_paused;
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
        pause();
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

void GameWidget::timerEvent(QTimerEvent *timerEvent)
{
    if(m_preStartTimer->remainingSec())
    {
        m_timeBeforeBeginRemainingLabel.setText(QString::number(m_preStartTimer->remainingSec()));
    }
    else
    {
        if(!m_paused)
        {
            if (m_scene)
            {

                if(m_scene->isFinished())
                {
                    killTimer(timerEvent->timerId());
                    emit showScore("Score");
                }
                else
                {
                    /// mise à jour de la scène
                    m_scene->update();

                     /// mise à jour de la caméra
                    View view = m_scene->calcViewPoint();
                    centerOn(view.position());
                    // "crante" l'effet de zoom, car visiblement, changer l'échelle de la vue dans qt prend du temps
                    // et ralenti considérablement le jeu lorsque cela est fait à chaque frame.
                    //float zoom = (int)(view.zoom()*200)/200.f;
                    //std::cout << view.zoom() << " --- " << zoom << " --- " << m_cameraScale << std::endl;
                    m_frameCount++;
                    if (m_frameCount == 3)
                        m_frameCount = 0;
                    if (m_frameCount == 0)
                    {
                        std::cout << "Application du zoom" << std::endl;
                        if (view.zoom() != m_cameraScale)
                        {
                            float cameraScale = 1 - (m_cameraScale - view.zoom());
                            m_cameraScale = view.zoom();
                            scale(cameraScale, cameraScale);
                        }
                    }

                    /// mise à jour du compteur (Affichage
                    m_timeLabel.setText(utils::showableTime(m_scene->time().elapsed()));

                    /// mise à jour du nombre de checkpoint restant (Affichage)
                    QString checkpointRemainingString = "Checkpoint Restant(s) :"+QString::number(m_scene->checkpointListener()->checkpointRemaining());
                    m_checkpointRemainingLabel.setText(checkpointRemainingString);
                }
            }
        }
    }
}

void GameWidget::pause()
{
    if(!m_paused)
    {
        this->setCursor(Qt::ArrowCursor);
        m_paused=true;
        emit gamePaused(m_scene->time());

    }
}

void GameWidget::setPaused(bool paused)
{
    m_paused=paused;
}

void GameWidget::startGame()
{
    m_timeBeforeBeginRemainingLabel.hide();
    m_timeBeforeBeginRemainingLabel.deleteLater();
    scene()->start();
}

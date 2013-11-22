#include <QKeyEvent>
#include "gamewindow.h"
#include "ui_gamewindow.h"
#include <SFML/System/Time.hpp>
#include <QMessageBox>

GameWindow::GameWindow(QWidget *parent) :
    QDialog(parent),
    m_scene(nullptr),
    ui(new Ui::GameWindow)
{
    ui->setupUi(this);
    grabKeyboard();
    startTimer(sf::seconds(1/60.f).asMilliseconds());
}

GameWindow::~GameWindow()
{
    delete ui;
}


const PlayerInput& GameWindow::playerInput() const
{
    return m_playerInput;
}


Scene *GameWindow::scene() const
{
    return m_scene;
}

void GameWindow::setScene(Scene *scene)
{
    m_scene = scene;
    if (scene)
    {
        ui->graphicsView->setScene(scene->graphicsScene());
    }
    else
    {
        ui->graphicsView->setScene(nullptr);
    }
}


void GameWindow::keyPressEvent(QKeyEvent *event)
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

    default:
         QDialog::keyPressEvent(event);
    }
}

void GameWindow::keyReleaseEvent(QKeyEvent *event)
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

    default:
         QDialog::keyReleaseEvent(event);
    }
}

void GameWindow::timerEvent(QTimerEvent *)
{
    if (m_scene)
    {
        m_scene->update();
        ui->graphicsView->centerOn(m_scene->calcViewPoint());
        if(m_scene->isFinished())
        {
          //QMessageBox::information(nullptr, "Réussite", "Fin de course!");
        }
    }
}

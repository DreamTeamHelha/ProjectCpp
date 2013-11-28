#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "menu.h"
#include "formtools.h"
#include <QMessageBox>
#include "pausemenu.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_panel(nullptr),
    m_gameWidget(nullptr)
{
    ui->setupUi(this);

    showPanel("Menu");
}

MainWindow::~MainWindow()
{
    delete ui;
}

Panel *MainWindow::panel() const
{
    return m_panel;
}

GameWidget *MainWindow::gameWidget() const
{
    return m_gameWidget;
}

void MainWindow::showPanel(const QString &menuName)
{
    // nettoyage
    if (m_panel)
    {
        m_panel->close();
        m_panel->deleteLater();
        m_panel = nullptr;
    }
    if(m_gameWidget)
    {
        m_gameWidget->close();
        m_gameWidget->deleteLater();
        m_gameWidget = nullptr;
    }

    // crée le panel correspondant
    if (menuName == "Menu")
    {
        m_panel = new Menu(this);
    }
    else if (menuName == "Tools")
    {
        m_panel = new FormTools(this);
    }

    // crée les connexions
    if (m_panel)
    {
        connect(m_panel, SIGNAL(showPanel(QString)), this, SLOT(showPanel(QString)));
        connect(m_panel, SIGNAL(startGame(QString,QString)), this, SLOT(startGame(QString,QString)));
        m_panel->show();
    }
}

void MainWindow::startGame(const QString &levelName, const QString &carClassName)
{
    Scene *scene = new Scene;
    if (scene->load(levelName, carClassName))
    {
        // changement de niveau
        if (m_panel)
        {
            m_panel->close();
            m_panel->deleteLater();
            m_panel = nullptr;
        }
        if (m_gameWidget)
        {
            m_gameWidget->close();
            m_gameWidget->deleteLater();
        }

        m_gameWidget = new GameWidget(scene, this);
        m_gameWidget->setGeometry(0,0,800,600);
        m_gameWidget->show();
        connect(m_gameWidget,SIGNAL(gamePaused(QTime)),this,SLOT(pauseGame(QTime)));
    }
    else
    {
        // reste où il est
        delete scene;
        QMessageBox::information(this, "Erreur", "Le chargement du niveau '" + levelName + "' avec le véhicule '" + carClassName + "' a échoué!", 0);
    }
}

void MainWindow::pauseGame(QTime)
{
    if(!m_gameWidget)
    {
        std::cout<<"Pas de game Widget disponible"<<std::endl;
        return;
    }
    m_panel = new PauseMenu(m_gameWidget->scene()->time().elapsed(),m_gameWidget);
    m_panel->show();
    std::cout<<"Affichage Menu Pause"<<std::endl;
}

void MainWindow::continueGame()
{
    m_gameWidget->scene()->setTime((dynamic_cast<PauseMenu*>(m_panel))->time());
    m_panel->close();
    m_panel->deleteLater();
    m_panel = nullptr;
    m_gameWidget->setPaused(false);

}

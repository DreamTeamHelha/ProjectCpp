#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "menu.h"
#include "formtools.h"
#include <QMessageBox>
#include "pausemenu.h"
#include "credits.h"
#include "choosewidget.h"
#include "scorewindow.h"
#include <QSound>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_panel(nullptr),
    m_gameWidget(nullptr),
    m_soundMenu(nullptr)
{
    ui->setupUi(this);
    /* TEST
    QPixmap cursor(QCoreApplication::applicationDirPath() + "/data/carSirto.png");
    this->setCursor( QCursor(cursor,0,0) );
    */

    showPanel("Menu");
}

MainWindow::~MainWindow()
{
    delete ui;
    if(m_soundMenu)
    {
        delete m_soundMenu;
    }
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
    if(m_soundMenu==nullptr)
    {
        m_soundMenu= new QSound(QCoreApplication::applicationDirPath() + "/data/sons/1.wav");
        m_soundMenu->play();
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
    else if (menuName == "Credit")
    {
        m_panel = new credits(this);
    }
    else if (menuName == "Choose")
    {
        m_panel = new ChooseWidget(this);
    }
    else if (menuName == "Score")
    {
        m_panel = new ScoreWindow(this,m_gameWidget->scene()->time().elapsed(),m_gameWidget->scene()->trackName());
     }

    if(m_gameWidget)
    {
        m_gameWidget->close();
        m_gameWidget->deleteLater();
        m_gameWidget = nullptr;
    }

    // crée les connexions
    if (m_panel)
    {
        connect(m_panel, SIGNAL(showPanel(QString)), this, SLOT(showPanel(QString)));
        std::cout<<"Pas de bug 1"<<std::endl;
        connect(m_panel, SIGNAL(startGame(QString,QString)), this, SLOT(startGame(QString,QString)));
        std::cout<<"Pas de bug 2"<<std::endl;
        m_panel->show();
        std::cout<<"Pas de bug 3"<<std::endl;


    }
}

void MainWindow::startGame(const QString &levelName, const QString &carClassName)
{
    if(m_soundMenu)
    {
        delete m_soundMenu;
        m_soundMenu=nullptr;
    }
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
            m_gameWidget = nullptr;
        }

        m_gameWidget = new GameWidget(scene, this);
        m_gameWidget->setGeometry(0,0,800,600);
        m_gameWidget->show();
        connect(m_gameWidget,SIGNAL(gamePaused(QTime)),this,SLOT(pauseGame(QTime)));
        connect(m_gameWidget, SIGNAL(showScore(QString)), this, SLOT(showPanel(QString)));
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
    m_gameWidget->setCursor(Qt::BlankCursor);
    m_gameWidget->setPaused(false);

}

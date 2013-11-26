#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "menu.h"
#include "formtools.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_panel(nullptr)
{
    ui->setupUi(this);

    showPanel("Menu");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::afficherMenu()
{
    Menu *menu= new Menu(this);
    menu->show();
}

void MainWindow::showPanel(const QString &menuName)
{
    if (m_panel)
    {
        m_panel->close();
        m_panel->deleteLater();
        m_panel = nullptr;
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

}

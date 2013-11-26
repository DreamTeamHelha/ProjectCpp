#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "menu.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_panel(nullptr)
{
    ui->setupUi(this);

    afficherMenu();
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

}

void MainWindow::startGame(const QString &levelName, const QString &carClassName)
{

}

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "menu.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
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
void MainWindow::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);
}
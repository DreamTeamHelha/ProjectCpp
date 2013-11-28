#include "pausemenu.h"
#include <iostream>
#include <mainwindow.h>

PauseMenu::PauseMenu(const int time, QWidget *parent): Panel(parent), m_time(time)
{
    this->setGeometry(200,175,400,250);
    this->setStyleSheet("background:black;");


    m_continueButton = new QPushButton(this);
    m_continueButton->setText("Continue");
    m_continueButton->setGeometry(25,50,350,50);
    m_continueButton->setStyleSheet("background:white");
    connect(m_continueButton,SIGNAL(clicked()),this,SLOT(continueClicked()));

    m_quitButton = new QPushButton(this);
    m_quitButton->setText("Quit to main menu");
    m_quitButton->setGeometry(25,150,350,50);
    m_quitButton->setStyleSheet("background:white");
    connect(m_quitButton,SIGNAL(clicked()),this,SLOT(quitClicked()));
}

void PauseMenu::quitClicked()
{
    (dynamic_cast<MainWindow*> (this->parent()->parent()))->showPanel("Menu");
}

void PauseMenu::continueClicked()
{
    (dynamic_cast<MainWindow*> (this->parent()->parent()))->continueGame();
}

PauseMenu::~PauseMenu()
{
    delete m_continueButton;
    delete m_quitButton;
}

int PauseMenu::time()const
{
    return m_time;
}


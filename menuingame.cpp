#include "menuingame.h"
#include "ui_menuingame.h"

MenuInGame::MenuInGame(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MenuInGame)
{
    ui->setupUi(this);
}

MenuInGame::~MenuInGame()
{
    delete ui;
}

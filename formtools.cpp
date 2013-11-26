#include "formtools.h"
#include "ui_formtools.h"
#include "menu.h"
#include <iostream>

FormTools::FormTools(QWidget *parent) :
    Panel(parent),
    ui(new Ui::FormTools)
{
    ui->setupUi(this);

    connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(afficherMenu()));
}

FormTools::~FormTools()
{
    std::cout << "FormTools deleted" << std::endl;
    delete ui;
}

void FormTools::afficherMenu()
{
    emit showPanel("Menu");
}

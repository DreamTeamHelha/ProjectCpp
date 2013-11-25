#include "formtools.h"
#include "ui_formtools.h"
#include "menu.h"

FormTools::FormTools(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormTools)
{
    ui->setupUi(this);
    QObject::connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(afficherMenu()));

}

FormTools::~FormTools()
{
    delete ui;
}
void FormTools::afficherMenu()
{
    this->close();
    Menu *menu=new Menu(this->parentWidget());

    menu->show();
}

#include "menu.h"
#include "ui_menu.h"

#include"formtools.h"
#include"gamewidget.h"
#include<QMessageBox>
Menu::Menu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Menu)
{
    ui->setupUi(this);
    QObject::connect(ui->b_Settings,SIGNAL(clicked()),this,SLOT(afficherTools()));
    QObject::connect(ui->b_Exit,SIGNAL(clicked()),this,SLOT(exitApp()));
    QObject::connect(ui->b_Race,SIGNAL(clicked()),this,SLOT(AfficherJeu()));

    ui->b_Race->setIcon(QIcon("SirtoliRacing/data/img/SIRTOLI_LOGOMenu.jpg"));



}

Menu::~Menu()
{
    delete ui;
}

void Menu::afficherTools()
{
    this->close();
    FormTools *tools=new FormTools(this->parentWidget());

    tools->show();
}

void Menu::exitApp()
{
   qApp->quit();
}
void Menu::AfficherJeu()
{
    this->close();
     GameWidget *gameWidget(nullptr);
     Scene *scene = new Scene();

     // initialisation des factories


     // chargement de la map
     if (scene->load("Raph_Paradise", "Car"))
     {
         // -- test -- paramétrage de la scène
         //gameWindow.setScene(&scene);
         //scene.setPlayerInput(&gameWindow.playerInput());
         gameWidget = new GameWidget(scene, this->parentWidget());
         gameWidget->setGeometry(0,0,this->parentWidget()->width(),this->parentWidget()->height());
     }
     else
     {
         QMessageBox::information(nullptr, "Erreur", "Le chargement de la map à échoué", 0);
         gameWidget = new GameWidget(nullptr);
     }
     // exécution du programme

     gameWidget->show();




}

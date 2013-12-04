#include "scene.h"
#include "scorewindow.h"
#include "ui_scorewindow.h"
#include <iostream>



ScoreWindow::ScoreWindow(QWidget *parent,int timeElapsed) :
    Panel(parent),
    m_time(timeElapsed),
    ui(new Ui::ScoreWindow)
{
    std::cout<<"Erreur de lecture"<<std::endl;

    ui->setupUi(this);
    QString val;
    QJsonObject item;
    QString name;
    int time;

    //Score s;
    QFile file(QCoreApplication::applicationDirPath() + "/data/score.json");


    file.open(QIODevice::ReadOnly | QIODevice::Text);
    if(!file.isOpen())
    {
        std::cout<<"Erreur de lecture"<<std::endl;
    }

    val = file.readAll();
    file.close();

    QJsonDocument document = QJsonDocument::fromJson(val.toUtf8());
    /*if(document.isEmpty())
    {
        return false;
    }*/

    QJsonArray root = document.array();
    for(int i=0;i<root.count();i++)
    {
        item =root[i].toObject();
        name=item["Name"].toString();
        time=item["Time"].toDouble();
        //Score s(time,name);


       //scores[i]=s;

       itemTime=new QStandardItem(QString::number(time));
        colTime.append(itemTime);
        itemName=new QStandardItem(QString(name));
        colName.append(itemName);


       // ind[i]=i;



  }
  /*  for(int i=0;i<root.count()-1;i++){
        for(int j=i+1;j<root.count();j++){
            if(scores[i]>scores[j]){
            inter=ind[i];
            ind[i]=ind[j];
            ind[j]=inter;
            }

        }
    }
    for(int i=0;i<root.count();i++){
        itemTime=new QStandardItem(QString::number(scores[ind[i]].time()));
        colTime.append(itemTime);
        itemName=new QStandardItem(QString(scores[ind[i]].name()));
        colTime.append(itemName);
        model->appendRow(colTime);
        //colTime.removeFirst();
        //colTime.clear();

    }*/



 model->appendColumn(colName);
  model->appendColumn(colTime);

  model->setHorizontalHeaderItem(0, new QStandardItem(QString("Name")));
  model->setHorizontalHeaderItem(1, new QStandardItem(QString("Time")));

 ui->tableView->setModel(model);

 connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(addScore()));

}

ScoreWindow::~ScoreWindow()
{
    delete ui;
}


void ScoreWindow::addScore()
{


    QString val;
    QJsonObject item;
    QJsonObject item2;
    QString name;
    int time;
    QFile file("C:/Users/Olivier/Desktop/Score.json");
    Scene m_scene;


    file.open(QIODevice::ReadOnly | QIODevice::Text);
    /*if(!file.isOpen())
    {
        return false;
    }*/

    val = file.readAll();
    file.close();

    QJsonDocument document = QJsonDocument::fromJson(val.toUtf8());
    /*if(document.isEmpty())
    {
        return false;
    }*/

    QJsonArray root = document.array();
    for(int i=0;i<root.count();i++)
    {

        item =root[i].toObject();
        name=item["Name"].toString();
        time=item["Time"].toDouble();

     }
    QString nom2= ui->nameText->toPlainText();
    time=m_time;

    item2.insert("Name",nom2);
    item2.insert("Time",time);


   root.insert(root.count(),item2);

    qDebug()<<root;

    file.open(QFile::WriteOnly | QFile::Truncate);

   /* if(!file.isOpen())
    {
        return false;
    }*/

    file.write(QJsonDocument(root).toJson());
    ui->setupUi(this);

    itemTime=new QStandardItem(QString::number(time));

    itemName=new QStandardItem(QString(nom2));
    colScore.append(itemName);
    colScore.append(itemTime);


    model->appendRow(colScore);

    emit showPanel("Menu");









}

void ScoreWindow::afficherMenu()
{
   // showPanel("Menu");
}




/*bool load2(const QString& filename)
{


    QString val;
    QJsonObject item;
    QJsonObject item2;
    QString name;
    int time;
    QFile file(filename);


    file.open(QIODevice::ReadOnly | QIODevice::Text);
    if(!file.isOpen())
    {
        return false;
    }

    val = file.readAll();
    file.close();

    QJsonDocument document = QJsonDocument::fromJson(val.toUtf8());
    if(document.isEmpty())
    {
        return false;
    }

    QJsonArray root = document.array();
    Score *inter;
    for(int i=0;i<root.count();i++)
    {
        for(int j=1;i<root.count();j++)
        {
        item =root[i].toObject();
        name=item["Name"].toString();
        time=item["Time"].toDouble();
        Score* s=new Score(time,name);
        item =root[j].toObject();
        name=item["Name"].toString();
        time=item["Time"].toDouble();
        Score* s2=new Score(time,name);
        if(s>s2){
            inter=s;
            s=s2;
            s2=inter;

        }
        }



     }
    QString nom2="nom";

    item2.insert("Name",nom2);
    item2.insert("Time",100);


   root.insert(root.count(),item2);

    qDebug()<<root;

    file.open(QFile::WriteOnly | QFile::Truncate);

    if(!file.isOpen())
    {
        return false;
    }

    file.write(QJsonDocument(root).toJson());

}*/


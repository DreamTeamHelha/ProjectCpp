#include "scorewindow.h"
#include "ui_scorewindow.h"
#include <iostream>
#include <QMessageBox>
#include <utils.h>



ScoreWindow::ScoreWindow(QWidget *parent,int timeElapsed) :
    Panel(parent),
    m_time(timeElapsed),
    ui(new Ui::ScoreWindow)
{
    ui->setupUi(this);
    load();
    loadTableView();
    connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(addScore()));
}

ScoreWindow::~ScoreWindow()
{
    delete ui;
    for(Score* score : m_scoreVector)
    {
        delete score;
    }
    std::cout<<"ScoreWindow deleted"<<std::endl;
}


void ScoreWindow::addScore()
{
/*

    QString val;
    QJsonObject item;
    QJsonObject item2;
    QString name;
    int time;
    QFile file("C:/Users/Olivier/Desktop/Score.json");
    Scene m_scene;


    val = file.readAll();
    file.close();

    QJsonDocument document = QJsonDocument::fromJson(val.toUtf8());
    if(document.isEmpty())
    {
        return false;
    }

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

    if(!file.isOpen())
    {
        return false;
    }

    file.write(QJsonDocument(root).toJson());
    ui->setupUi(this);

    itemTime=new QStandardItem(QString::number(time));

    itemName=new QStandardItem(QString(nom2));
    colScore.append(itemName);
    colScore.append(itemTime);


    model->appendRow(colScore);

    emit showPanel("Menu");*/
}

void ScoreWindow::load()
{
    //Lecture du fichier de score
    QFile file(QCoreApplication::applicationDirPath() + "/data/score.json");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    if(!file.isOpen())
    {
        QMessageBox::information(nullptr, "Erreur", "Le fichier de score n'est pas trouve!");
    }

    QString val = file.readAll();
    file.close();

    //Transformation du contenu du fichier en tableau JSON
    QJsonDocument document = QJsonDocument::fromJson(val.toUtf8());
    if(document.isEmpty())
    {
       QMessageBox::information(nullptr, "Erreur", "Le fichier de score n'est pas trouve!");
    }

    QJsonArray root = document.array();
    for(int i=0;i<root.count();i++)
    {
        QJsonObject item =root[i].toObject();
        Score * score = new Score(item["Time"].toDouble(),item["Name"].toString());
        m_scoreVector.append(score);
     }
}

void ScoreWindow::loadTableView()
{
    QStandardItemModel *model= new QStandardItemModel(0,0,0);
    QList<QStandardItem*> colTime;
     QList<QStandardItem*> colName;

     QStandardItem *item;
     for(Score * score: m_scoreVector)
     {
         item = new QStandardItem(score->name());
         colName.append(item);

         item = new QStandardItem(utils::showableTime(score->time()));
         colTime.append(item);
     }
      model->appendColumn(colName);
      model->appendColumn(colTime);

      model->setHorizontalHeaderItem(0, new QStandardItem(QString("Name")));
      model->setHorizontalHeaderItem(1, new QStandardItem(QString("Time")));

      ui->tableView->setModel(model);
}



#include "formtools.h"
#include "ui_formtools.h"
#include "menu.h"
#include <iostream>
#include<QFile>
#include"utils.h"
#include"tracklist.h"
#include"QMessageBox"
#include"QJsonDocument"
#include"QStandardItemModel"
#include"QJsonArray"
#include"QJsonObject"
#include"QList"
FormTools::FormTools(QWidget *parent) :
    Panel(parent),
    ui(new Ui::FormTools)
{
    ui->setupUi(this);

    connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(afficherMenu()));
    connect(ui->nextButton,SIGNAL(clicked()),this,SLOT(nextTrack()));
    connect(ui->previousButton,SIGNAL(clicked()),this,SLOT(previousTrack()));

    m_trackList = new TrackList();
    m_trackList->load();

    //ui->trackPicture->setPixmap(QCoreApplication::applicationDirPath() + "/data/tracks/" + m_trackList->currentTrack());
    ui->trackName->setText(m_trackList->currentTrackName());
    load();
}

FormTools::~FormTools()
{
    std::cout << "FormTools deleted" << std::endl;
    delete ui;
    delete m_trackList;
}

void FormTools::afficherMenu()
{
    emit showPanel("Menu");
}

void FormTools::load()
{
    //Lecture du fichier de score
    QFile file(QCoreApplication::applicationDirPath() + "/data/tracks/" + m_trackList->currentTrack() +".score");
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

    QStandardItemModel *model= new QStandardItemModel(0,0,0);

    QList<QStandardItem*> colTime;
    QList<QStandardItem*> colName;


    QJsonArray root = document.array();
    for(int i=0;i<root.count();i++)
    {
        QJsonObject item =root[i].toObject();


        colName.append( new QStandardItem(item["Name"].toString()));
        colTime.append( new QStandardItem(utils::showableTime(item["Time"].toDouble())));

     }
    model->appendColumn(colName);
    model->appendColumn(colTime);

    model->setHorizontalHeaderItem(0, new QStandardItem(QString("Name")));
    model->setHorizontalHeaderItem(1, new QStandardItem(QString("Time")));

    ui->tableView->setModel(model);


}
void FormTools::nextTrack()
{
    m_trackList->next();
    //ui->trackPicture->setPixmap(QCoreApplication::applicationDirPath() + "/data/tracks/" + m_trackList->currentTrack());
    ui->trackName->setText(m_trackList->currentTrackName());

    load();
}

void FormTools::previousTrack()
{
    m_trackList->previous();
    //ui->trackPicture->setPixmap(QCoreApplication::applicationDirPath() + "/data/tracks/" + m_trackList->currentTrack());
    ui->trackName->setText(m_trackList->currentTrackName());
    load();
}

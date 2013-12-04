#ifndef SCOREWINDOW_H
#define SCOREWINDOW_H
#include "score.h"
#include "scene.h"
#include <QFile>
#include <QJsonDocument>
#include <QString>
#include <QJsonArray>
#include <QJsonObject>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QList>
#include <QTime>
#include <QDebug>
#include <vector>
using namespace std;


#include "panel.h"

#include <QWidget>
using namespace std;

namespace Ui {
class ScoreWindow;
}

class ScoreWindow : public Panel
{
    Q_OBJECT

public:
    explicit ScoreWindow(QWidget *parent = 0,int m_time =0);
    ~ScoreWindow();

    //bool load(const QString& filename);
    //void addScore();
   // void addScore(const QString& filename);
private slots:

    void addScore();
    void afficherMenu();

private:
    Ui::ScoreWindow *ui;
     //QStandardItemModel *model;
     QStandardItemModel *model= new QStandardItemModel(0,0,0);
     QList<QStandardItem*> colTime;
      QList<QStandardItem*> colName;
      QList<QStandardItem*> colScore;
      QStandardItem* itemTime;
      QStandardItem* itemName;
      int           m_time;

   // void addScore(const QString& filename);

};

#endif // SCOREWINDOW_H

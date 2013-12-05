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
#include <QVector>
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
    void load();
    void loadTableView();

private slots:

    void addScore();

private:
    Ui::ScoreWindow *ui;

      int           m_time;
      QVector<Score *> m_scoreVector;

   // void addScore(const QString& filename);

};

#endif // SCOREWINDOW_H

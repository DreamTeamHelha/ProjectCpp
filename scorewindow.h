#pragma once
#include "score.h"
#include <QString>
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
    explicit ScoreWindow(QWidget *parent = 0,int time =0,QString track = "noTrack");
    ~ScoreWindow();
    void load();
    void loadTableView();
    int ranked() const;
private slots:
    void addScore();
    void backToMenu();
private:
    Ui::ScoreWindow   *ui;
    int               m_time;
    int               m_rank;
    QString           m_track;
    QVector<Score *>  m_scoreVector;
};


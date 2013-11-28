#pragma once
#include "panel.h"
#include <QPushButton>
#include <QTime>

class PauseMenu : public Panel
{
    Q_OBJECT
public:
    PauseMenu(const int,QWidget *);
    ~PauseMenu();
    int time()const;

public slots:
    void continueClicked();
    void quitClicked();
signals:
    void continueGame();

private:
    QPushButton *m_continueButton;
    QPushButton *m_quitButton;
    int        m_time;

};


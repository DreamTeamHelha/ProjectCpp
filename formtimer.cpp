#include "formtimer.h"
#include "ui_formtimer.h"

#include <QTimer>
#include<iostream>
using namespace std;

FormTimer::FormTimer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormTimer)
{
    ui->setupUi(this);
    m_timer_value=0;
    m_timer_Min_value=0;
    ui->m_timeLabel->setText("temps :0");
    this->m_timer = new QTimer(this);
           // À chaque fin d'intervalle, exécution du slot update()
    connect(this->m_timer, SIGNAL(timeout()), this, SLOT(update()));
           // On applique un intervalle d'une seconde (1000 ms) entre chaque timeout du timer
    this->m_timer->setInterval(100);
    this->m_timer->start();

}

FormTimer::~FormTimer()
{
    delete ui;
    delete m_timer;
    delete m_timer_Min_value;
}

void FormTimer::update()
{

 m_timer_value++;

    if(m_timer_value%60==0)
    {
         m_timer_Min_value++;
        m_timer_value=0;
    }

    QString tempsSec = QString::number(m_timer_value);
     QString tempsMin = QString::number(m_timer_Min_value);
    ui->m_timeLabel->setText("Temps :   "+tempsMin+":"+tempsSec);
}

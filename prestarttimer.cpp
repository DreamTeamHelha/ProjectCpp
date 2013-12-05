#include "prestarttimer.h"
#include <QTimerEvent>
#include "gamewidget.h"
PreStartTimer::PreStartTimer(QObject *parent) :
    QObject(parent),
    m_remainingSec(3)
{
    startTimer(1000);
}

const int PreStartTimer::remainingSec()const
{
    return m_remainingSec;
}

 void PreStartTimer::timerEvent(QTimerEvent *event)
 {
     m_remainingSec--;
     if(!m_remainingSec)
     {
         emit endTimer();
         killTimer(event->timerId());
     }
 }


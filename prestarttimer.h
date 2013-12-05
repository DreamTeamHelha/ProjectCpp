#pragma once

#include <QObject>

class PreStartTimer : public QObject
{
    Q_OBJECT
public:
    explicit PreStartTimer(QObject *parent = 0);
    const int remainingSec()const;

protected:
    void timerEvent(QTimerEvent *event);

private:
    int m_remainingSec;
signals:
    void endTimer();

};


#ifndef FORMTIMER_H
#define FORMTIMER_H

#include <QWidget>
#include<QTimer>

namespace Ui {
class FormTimer;
}

class FormTimer : public QWidget
{
    Q_OBJECT

public:
    explicit FormTimer(QWidget *parent = 0);
    ~FormTimer();
private slots:
    void update();

private:
    Ui::FormTimer *ui;
    QTimer *m_timer;
    int m_timer_Min_value;
    int m_timer_value;
};

#endif // FORMTIMER_H

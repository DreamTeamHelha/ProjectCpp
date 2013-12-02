#ifndef CREDITS_H
#define CREDITS_H

#include <QWidget>
#include "panel.h"
namespace Ui {
class credits;
}

class credits : public Panel
{
    Q_OBJECT

public:
    explicit credits(QWidget *parent = 0);
    ~credits();
public slots:
    void afficherMenu();
private:
    Ui::credits *ui;
};

#endif // CREDITS_H

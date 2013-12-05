#pragma once

#include "panel.h"


namespace Ui {
class Menu;
}

class Menu : public Panel
{
    Q_OBJECT

public:

    explicit Menu(QWidget *parent = 0);
    ~Menu();

private slots:

    void afficherTools();
    void exitApp();
    void AfficherJeu();
    void afficherCredit();

private:

    Ui::Menu *ui;

};

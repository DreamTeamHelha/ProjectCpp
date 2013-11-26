#pragma once

#include "panel.h"
#include <QSound>

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

private:

    Ui::Menu *ui;
    QSound   *m_soundMenu;
};

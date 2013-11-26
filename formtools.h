#pragma once

#include "panel.h"

namespace Ui {
class FormTools;
}

class FormTools : public Panel
{
    Q_OBJECT

public:
    explicit FormTools(QWidget *parent = 0);
    ~FormTools();

private slots:

    void afficherMenu();

private:

    Ui::FormTools *ui;
};

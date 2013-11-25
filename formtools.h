#ifndef FORMTOOLS_H
#define FORMTOOLS_H

#include <QWidget>

namespace Ui {
class FormTools;
}

class FormTools : public QWidget
{
    Q_OBJECT

public:
    explicit FormTools(QWidget *parent = 0);
    ~FormTools();
signals:
private slots:

    void afficherMenu();

private:
    Ui::FormTools *ui;
};

#endif // FORMTOOLS_H

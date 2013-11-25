#ifndef MENUINGAME_H
#define MENUINGAME_H

#include <QWidget>

namespace Ui {
class MenuInGame;
}

class MenuInGame : public QWidget
{
    Q_OBJECT

public:
    explicit MenuInGame(QWidget *parent = 0);
    ~MenuInGame();

private:
    Ui::MenuInGame *ui;
};

#endif // MENUINGAME_H

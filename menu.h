#ifndef MENU_H
#define MENU_H

#include <QWidget>
#include<QSound>
namespace Ui {
class Menu;
}

class Menu : public QWidget
{
    Q_OBJECT
private:
    QSound *m_soundMenu;
public:
    explicit Menu(QWidget *parent = 0);

    ~Menu();
signals:
private slots:
    void afficherTools();
    void exitApp();
    void AfficherJeu();
private:
    Ui::Menu *ui;
};

#endif // MENU_H

#pragma once

#include <QMainWindow>
#include <QString>
#include "panel.h"

namespace Ui {
class MainWindow;
}

///
/// Fenêtre principale. Créée au début du jeu, détruite à la fin.
/// Contient les différents panels de menu, ainsi que gamewidget.
///
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void afficherMenu();

    ///
    /// Panel actuellement affiché dans la fenêtre
    ///
    Panel *panel() const;

public slots:

    ///
    /// Provoque le changement de menu
    ///
    void showPanel(const QString& menuName);

    ///
    /// Provoque le lancement du jeu.
    ///
    void startGame(const QString& levelName, const QString& carClassName);

private:

    Ui::MainWindow *ui;

    Panel *m_panel;
};


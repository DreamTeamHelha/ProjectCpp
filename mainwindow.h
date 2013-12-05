#pragma once

#include <QMainWindow>
#include <QString>
#include "panel.h"
#include "gamewidget.h"
#include <QSound>
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

    ///
    /// Getters
    ///
    Panel      *panel() const;
    GameWidget *gameWidget() const;

public slots:

    ///
    /// Provoque le changement de menu
    ///
    void showPanel(const QString& menuName);

    ///
    /// Provoque le lancement du jeu.
    ///
    void startGame(const QString& levelName, const QString& carClassName);

    ///
    /// Provoque la mise en pause du jeu
    ///
    void pauseGame(QTime);

    ///
    /// Provoque la fin de la pause
    ///
    void continueGame();


private:

    Ui::MainWindow *ui;

    Panel      *m_panel;
    GameWidget *m_gameWidget;
    QSound   *m_soundMenu;
};


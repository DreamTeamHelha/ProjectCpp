#pragma once

#include <QFrame>
#include <QString>

class Panel : public QFrame
{
    Q_OBJECT
public:
    explicit Panel(QWidget *parent = 0);

signals:

    ///
    /// Provoque le changement de menu
    ///
    void showPanel(const QString& menuName);

    ///
    /// Provoque le lancement du jeu.
    ///
    void startGame(const QString& levelName, const QString& carClassName);
};


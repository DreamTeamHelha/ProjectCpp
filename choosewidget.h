#ifndef CHOOSEWIDGET_H
#define CHOOSEWIDGET_H

#include <QWidget>
#include "tracklist.h"
#include "panel.h"

namespace Ui {
class ChooseWidget;
}

class ChooseWidget : public Panel
{
    Q_OBJECT

public:
    explicit ChooseWidget(QWidget *parent = 0);
    ~ChooseWidget();

private slots:
    ///
    /// Lance le jeu avec le circuit (et la voiture) choisis
    ///
    void launchGame();
    ///
    /// Affiche le circuit suivant
    ///
    void nextTrack();

    ///
    /// Affiche le circuit précédent
    ///
    void previousTrack();

    ///
    /// Affiche le menu principal
    ///
    void backToMenu();

private:
    Ui::ChooseWidget *ui;
    TrackList        *m_trackList;
};

#endif // CHOOSEWIDGET_H

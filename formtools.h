#pragma once

#include "panel.h"
#include "tracklist.h"

namespace Ui {
class FormTools;
}

class FormTools : public Panel
{
    Q_OBJECT

public:
    explicit FormTools(QWidget *parent = 0);
    ~FormTools();
    void load();

private slots:

    void afficherMenu();
    ///
    /// Affiche le circuit suivant
    ///
    void nextTrack();

    ///
    /// Affiche le circuit précédent
    ///
    void previousTrack();


private:

    Ui::FormTools *ui;
    TrackList *m_trackList;

};

#pragma once

#include <QVector>

class TrackList
{
private:
    QVector<QString> m_trackList;
    QVector<QString> m_nameList;
    int              m_currentIndex;
public:
    TrackList(int currentIndex=0);
    ~TrackList();
    ///
    /// Modifie la liste de circuits
    ///
    void setTrackList(QVector<QString>);

    ///
    /// Modifie la liste des circuits
    ///
    void setNameList(QVector<QString>);

    ///
    /// Permet de mettre le circuit suivant en tant que circuit courant
    ///
    void next();

    ///
    /// Permet de mettre le circuit précédent en tant que circuit courant
    ///
    void previous();

    ///
    /// Renvoie le nom du circuit courant (utilisé pour les fichiers
    ///
    QString currentTrack()const;

    ///
    /// Renvoie le nom à afficher du circuit courant
    ///
    QString currentTrackName()const;

    ///
    /// Permet de charger la liste des circuits et de leur nom à afficher
    ///
    void load();

};



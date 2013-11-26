#pragma once
#include <QString>
class Score
{
private:
    ///
    /// Nom du joueur ayant réalisé le temps
    ///
    QString m_name;
    ///
    /// Temps réalisé par le joueur
    ///
    int     m_time;
public:
    Score(int time, QString name="Unknown");
    bool operator==(Score const& score2)const;
    bool operator<(Score const& score2)const;
    bool operator>(Score const& score2)const;
};


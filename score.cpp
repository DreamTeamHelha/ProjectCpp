#include "score.h"


Score::Score(int time, QString name) : m_name(name),m_time(time)
{}

bool Score::operator ==(Score const& score2)const
{
    return m_time==score2.m_time;
}

bool Score::operator <(Score const& score2)const
{
    return m_time < score2.m_time;
}

bool Score::operator >(Score const& score2)const
{
    return m_time > score2.m_time;
}

int Score::time() const{
    return m_time;
}
QString Score::name() const{
    return m_name;
}

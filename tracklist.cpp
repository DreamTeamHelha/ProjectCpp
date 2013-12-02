#include "tracklist.h"
#include <QJsonObject>
#include <QFile>
#include <QJsonDocument>
#include <QCoreApplication>
#include <QJsonObject>
#include <iostream>
#include <QJsonArray>

TrackList::TrackList(int currentIndex):
    m_currentIndex(currentIndex)
{
    m_trackList = QVector<QString>();
    m_nameList = QVector<QString>();
}

TrackList::~TrackList()
{}

void TrackList::setTrackList(QVector<QString> trackList)
{
    m_trackList = trackList;
}

void TrackList::setNameList(QVector<QString> nameList)
{
    m_nameList=nameList;
}

void TrackList::next()
{
    if(m_currentIndex == (m_trackList.size()-1))
    {
        m_currentIndex=0;
    }
    else
    {
        m_currentIndex++;
    }
}

void TrackList::previous()
{
    if(m_currentIndex == 0)
    {
        m_currentIndex = m_trackList.size()-1;
    }
    else
    {
        m_currentIndex--;
    }
}

QString TrackList::currentTrack()const
{
    return m_trackList.at(m_currentIndex);
}

QString TrackList::currentTrackName()const
{
    return m_nameList.at(m_currentIndex);
}

void TrackList::load()
{
    QString val;
    QJsonObject item;
    QFile file(QCoreApplication::applicationDirPath() + "/data/tracklist.json");

    file.open(QIODevice::ReadOnly | QIODevice::Text);
    if(!file.isOpen())
    {
        return;
    }

    val = file.readAll();
    file.close();

    QJsonDocument document = QJsonDocument::fromJson(val.toUtf8());
    if(document.isEmpty())
    {
        return;
    }


    QJsonArray root = document.array();
    for(int i=0;i<root.count();i++)
    {
        item =root[i].toObject();
        m_trackList.append(item["track"].toString());
        m_nameList.append(item["name"].toString());
    }
    m_currentIndex=0;
}


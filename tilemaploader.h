#pragma once
#include "tilemap.h"
#include <QString>
#include <QRgb>

class TilemapLoader
{
private:
    static const QRgb GRASS = 0xFF000000;
    static const QRgb ASPHALT = 0xFFFFFFFF;

    TilemapLoader() = delete;
    ~TilemapLoader() = delete;
    ///
    /// Permet le chargement de la tilemap à partir d'une image.
    ///
   static Tilemap* load(QString path);
};



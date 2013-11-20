#pragma once
#include "tilemap.h"
#include <QString>
#include <QRgb>

class TilemapLoader
{
private:
    static const QRgb GRASS = 0xFFFFFFFF;
    static const QRgb ASPHALT = 0xFF000000;
public:
    TilemapLoader() = delete;
    ~TilemapLoader() = delete;
    ///
    /// Permet le chargement de la tilemap à partir d'une image.
    ///
   static Tilemap* load(QString path);
};



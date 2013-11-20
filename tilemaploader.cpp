#include "tilemaploader.h"
#include <QImage>
#include <QCoreApplication>
#include <QMessageBox>
#include <QApplication>
#include <iostream>
#include <QColor>


Tilemap* TilemapLoader::load(QString path)
{

    QImage *image = new QImage(path);
    if(image->isNull())
    {
        QMessageBox::information(nullptr, "Erreur", "L'image n'est pas trouvée!");
        return nullptr;
    }

    Tilemap *tilemap = new Tilemap();

    tilemap->setHeight(image->height());
    tilemap->setWidth(image->width());
    for(int widthCount = 0;widthCount<image->width();widthCount++)
    {
        for(int heightCount = 0;heightCount<image->height(); heightCount++)
        {
            QRgb color = image->pixel(widthCount,heightCount);
            switch(color)
            {
            case ASPHALT: tilemap->setTile(heightCount,widthCount,GroundType::Asphalt);
                          break;
            default :     tilemap->setTile(heightCount,widthCount,GroundType::Grass);

            }

        }
    }


    return tilemap;
}


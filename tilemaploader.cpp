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
    for(int heightCount = 0;heightCount<image->height(); heightCount++)
    {
        for(int widthCount = 0;widthCount<image->width();widthCount++)
        {
            QRgb color = image->pixel(widthCount,heightCount);
            switch(color)
            {
            case ASPHALT: tilemap->setTile(widthCount,heightCount,GroundType::Asphalt);
                          break;
            case MUD:     tilemap->setTile(widthCount,heightCount,GroundType::Mud);
                          break;
            default :     tilemap->setTile(widthCount,heightCount,GroundType::Grass);

            }

        }
    }


    return tilemap;
}


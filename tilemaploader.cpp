#include "tilemaploader.h"
#include <QImage>
#include <QCoreApplication>
#include <QMessageBox>


Tilemap* TilemapLoader::load(QString path)
{

    QImage *image = new QImage(path);
    if(image->isNull())
    {
        QMessageBox::information(nullptr, "Erreur", "L'image n'est pas trouvée!");
        return nullptr;
    }

    Tilemap *tilemap = new Tilemap();
    tilemap->setWidth(image->width());
    tilemap->setHeight(image->height());
    for(int widthCount = 0;widthCount<image->width();widthCount++)
    {
        for(int heightCount = 0;heightCount < image->height(); heightCount++)
        {
            QRgb color = image->pixel(widthCount,heightCount);
            switch(color)
            {
            case ASPHALT: tilemap->setTile(widthCount,heightCount,GroundType::Asphalt);
                        break;
            default :     tilemap->setTile(widthCount,heightCount,GroundType::Grass);
            }

        }
    }


    return tilemap;
}


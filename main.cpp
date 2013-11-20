#include <QApplication>
#include "gamewindow.h"
#include "scene.h"
#include "objectfactory.h"
#include <QCoreApplication>
#include "tilemaploader.h"
#include "tilemap.h"


int main(int argc, char ** argv)
{
    QApplication app(argc, argv);
    GameWindow gameWindow;
    Scene scene;

    gameWindow.setScene(&scene);
    scene.setPlayerInput(&gameWindow.playerInput());

    Tilemap *tilemap;
    tilemap = TilemapLoader::load(QCoreApplication::applicationDirPath() + "/data/tracks/Raph_paradise.png");
    std::cout<<"Taille de la map :"<<tilemap->width()<<" x "<<tilemap->height()<<std::endl;
    for(int i = 0;i<tilemap->width();i++)
    {
        for(int j=0;j<tilemap->height();j++)
        {
            std::cout<<(int)tilemap->tile(i,j);
        }
        std::cout<<std::endl;
    }




    gameWindow.show();
    return app.exec();
}

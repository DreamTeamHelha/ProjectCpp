#include <QApplication>
#include "gamewindow.h"
#include "scene.h"
#include "objectfactories.h"
#include "tilemaploader.h"
#include <QCoreApplication>

int main(int argc, char ** argv)
{
    QApplication app(argc, argv);
    GameWindow gameWindow;
    Scene scene(TilemapLoader::load(QCoreApplication::applicationDirPath()+"/data/tracks/Raph_Paradise"));

    // -- test -- paramétrage de la scène
    gameWindow.setScene(&scene);
    scene.setPlayerInput(&gameWindow.playerInput());

    // initialisation des factories
    ObjectFactories::initialize();

    // chargement de la map
    scene.load();

    // exécution du programme
    gameWindow.show();
    int returnCode = app.exec();

    // destruction des factories
    ObjectFactories::finalize();

    return returnCode;
}

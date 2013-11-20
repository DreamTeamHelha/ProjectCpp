#include <QApplication>
#include "gamewindow.h"
#include "scene.h"
#include "objectfactories.h"

int main(int argc, char ** argv)
{
    QApplication app(argc, argv);
    GameWindow gameWindow;
    Scene scene;

    // -- test -- paramétrage de la scène
    gameWindow.setScene(&scene);
    scene.setPlayerInput(&gameWindow.playerInput());

    // initialisation des factories
    ObjectFactories::initialize();

    // exécution du programme
    gameWindow.show();
    int returnCode = app.exec();

    // destruction des factories
    ObjectFactories::finalize();

    return returnCode;
}

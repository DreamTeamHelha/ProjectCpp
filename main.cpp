#include <QApplication>
#include "gamewindow.h"
#include "scene.h"
#include "objectfactories.h"
#include "tilemaploader.h"
#include <QCoreApplication>
#include <QMessageBox>

int main(int argc, char ** argv)
{
    QApplication app(argc, argv);
    GameWindow gameWindow;
    Scene scene;

    // initialisation des factories
    ObjectFactories::initialize();

    // chargement de la map
    if (scene.load("Raph_Paradise", "Car"))
    {
        // -- test -- paramétrage de la scène
        gameWindow.setScene(&scene);
        scene.setPlayerInput(&gameWindow.playerInput());
    }
    else
    {
        QMessageBox::information(nullptr, "Erreur", "Le chargement de la map à échoué", 0);
    }
    // exécution du programme

    gameWindow.show();
    int returnCode = app.exec();

    // destruction des factories
    ObjectFactories::finalize();

    return returnCode;
}

#include <QApplication>
#include "gamewidget.h"
#include "scene.h"
#include "objectfactories.h"
#include "tilemaploader.h"
#include <QCoreApplication>
#include <QMessageBox>

int main(int argc, char ** argv)
{
    QApplication app(argc, argv);
    GameWidget *gameWidget(nullptr);
    Scene *scene = new Scene();

    // initialisation des factories
    ObjectFactories::initialize();

    // chargement de la map
    if (scene->load("Raph_Paradise", "Car"))
    {
        // -- test -- paramétrage de la scène
        //gameWindow.setScene(&scene);
        //scene.setPlayerInput(&gameWindow.playerInput());
        gameWidget = new GameWidget(scene);
    }
    else
    {
        QMessageBox::information(nullptr, "Erreur", "Le chargement de la map à échoué", 0);
        gameWidget = new GameWidget(nullptr);
    }
    // exécution du programme

    gameWidget->show();
    int returnCode = app.exec();

    // destruction des factories
    ObjectFactories::finalize();

    return returnCode;
}

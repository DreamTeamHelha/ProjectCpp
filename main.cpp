#include <QApplication>
#include "gamewindow.h"
#include "scene.h"

int main(int argc, char ** argv)
{
    QApplication app(argc, argv);
    GameWindow gameWindow;
    Scene scene;

    gameWindow.setScene(&scene);
    scene.setPlayerInput(&gameWindow.playerInput());

    gameWindow.show();
    return app.exec();
}

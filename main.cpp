#include <QApplication>
#include "objectfactories.h"
#include "mainwindow.h"

int main(int argc, char ** argv)
{
    QApplication app(argc, argv);

    // initialisation des factories
    ObjectFactories::initialize();

    // création de la fenêtre et exécution
    MainWindow w;
    w.show();
    w.setMaximumSize(800,600);
    w.setMinimumSize(800,600);

    int returnCode = app.exec();

    // destruction des factories
    ObjectFactories::finalize();

    return returnCode;
}

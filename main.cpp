#include <QApplication>
#include "gamewidget.h"
#include "scene.h"
#include "objectfactories.h"
#include "tilemaploader.h"
#include <QCoreApplication>
#include <QMessageBox>
#include"mainwindow.h"
int main(int argc, char ** argv)
{
    QApplication app(argc, argv);
    ObjectFactories::initialize();
    MainWindow w;
    w.show();
    w.setMaximumSize(800,600);
    w.setMinimumSize(800,600);

    //QWindow::setFixedSize(800,600);
    int returnCode = app.exec();
    // destruction des factories
    ObjectFactories::finalize();







    return returnCode;
}

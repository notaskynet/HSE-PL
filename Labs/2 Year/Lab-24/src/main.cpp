#include <QApplication>
#include "MainWindow.h"


int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    QCoreApplication::setAttribute(Qt::AA_DontUseNativeMenuBar);
    MainWindow main_window;
    main_window.show();
    return app.exec();
}
#include <QApplication>

#include "../include/mainwindow.hpp"


int main(int argv, char** args)
{
    QApplication app(argv, args);
    MainWindow *window = new MainWindow(500, 500);
    window->show(); 
    return app.exec();
}
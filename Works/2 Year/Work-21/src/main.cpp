#include "../include/keygen.h"
#include <QApplication>


int main(int argv, char** args)
{
    QApplication app(argv, args);
    KeyGenerator window;
    return app.exec();
}
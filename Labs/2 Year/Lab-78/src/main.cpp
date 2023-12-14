#include <QApplication>
#include "MainWindow.h"


/* Как работает программа?
*
* Класс MainWindow ответчает за отрисовку окна, с котором мы будем работать.
* В основном оске есть 2 вклаки: первая вкладка отвечает за редактор текста
* (в нем мы работаем с QTextEdit), а вторая будет отвечает за настройки (Она
* реадлизована на базе класса SettingsMenu).
*/


int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    MainWindow mainwindow;
    mainwindow.show();
    return app.exec();
}
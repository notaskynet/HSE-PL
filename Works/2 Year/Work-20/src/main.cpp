#include <QApplication>
#include <QTextEdit>
#include <QPushButton>
#include <QVBoxLayout>

#include "key_generator.h"




int main(int argv, char** argc)
{
    QApplication app(argv, argc);

    KeyGenerator key_generator;
    QPushButton  push_button("Generate key");
    
    QObject::connect(
        &push_button,
        SIGNAL(clicked()),
        &key_generator,
        SLOT(updateKey())
    );

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(key_generator.textEdit);
    layout->addWidget(&push_button);

    QWidget window;
    window.setLayout(layout);
    window.setWindowTitle("Key Generator");
    window.show();

    QObject::connect(
        (QObject*)viewer.engine(),
        SIGNAL(quit()),
        &app,
        SLOT(quit())
    );

    return app.exec();
}

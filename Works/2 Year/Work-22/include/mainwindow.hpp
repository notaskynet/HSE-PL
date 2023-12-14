#pragma once

#include <QWidget>
#include <QTextEdit>
#include <QPushButton>
#include <QString>
#include <QVBoxLayout>
#include <QStringList>
#include <QLineEdit>
#include <QLabel>
#include <QMap>
#include <QComboBox>
#include <QFileDialog>

#include "openssl_tools.hpp"


class MainWindow
{
public:
    MainWindow();
    MainWindow(int width, int height);
    ~MainWindow();

    void show();

private:
    void selectKey();
    void generateKey();
    void generateCertificate();

private:
    QWidget *window;

    QMap<QString, QLineEdit*> fields;
    QComboBox *crypto_list;
    QComboBox *hash_list;

    QTextEdit *certificate;
    QLineEdit *key_path;

    QPushButton *generate_certificate_button;
    QPushButton *generate_key_button;
    QPushButton *select_key_button;

    const QStringList cripto_algos = {
        "gost2001",
        "gost2012_256",
        "gost2012_512"
    };
    const QStringList hash_algos = {
        "md_gost94",
        "md_gost12_256",
        "md_gost12_512"
    };
};

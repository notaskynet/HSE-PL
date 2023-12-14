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

#include <sstream>
#include <fstream>
#include <string>


class KeyGenerator
{
public:
    KeyGenerator();
    KeyGenerator(int width, int height);

    ~KeyGenerator();
private:
    struct UserInformation;
    struct CommandOptions;

    void showCertificate();

    std::string generateKeyCertificate(
        const CommandOptions &cmd_options
    );

    std::string generateCommand(
        const CommandOptions &cmd_options
    );
private:
    QWidget *window;

    QMap<QString, QLineEdit*> fields;
    QComboBox *crypto_list;
    QComboBox *hash_list;
    QTextEdit *text_edit;
    QPushButton *generate_button;

    const QStringList algorithms = {
        "gost2001",
        "gost2012_256",
        "gost2012_512"
    };
    const QStringList hashes = {
        "md_gost94",
        "md_gost12_256",
        "md_gost12_512"
    };
};

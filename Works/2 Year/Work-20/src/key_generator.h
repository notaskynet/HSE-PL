#include <QTextEdit>
#include <QString>

#include <fstream>
#include <cstdio>
#include <sstream>
#include <string>
#include <cstdlib>


class KeyGenerator : public QWidget
{
    Q_OBJECT

public:
    QTextEdit* textEdit;
    KeyGenerator();
    ~KeyGenerator();

public slots:
    void updateKey();
};
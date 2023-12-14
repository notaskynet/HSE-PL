#ifndef __SETTINGS_MENU_H__
#define __SETTINGS_MENU_H__

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QFileDialog>
#include <QPushButton>
#include <QLineEdit>
#include <QComboBox>
#include <QLabel>
#include <QWidget>

#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QDebug>

class SettingsMenu : public QWidget
{
    Q_OBJECT
public:
    SettingsMenu(QWidget* parent = nullptr);
    ~SettingsMenu() = default;

    QString getFontSize() const;
    QString getFontColor() const;
    QString getBackgroundColor() const;
public slots:
    void saveChanges();
    void importXml();
    void exportXml();
signals:
    void fontSizeChanged();
    void fontColorChanged();
    void backgroundColorChanged();
private:
    QString fontSize = "14";
    QString fontColor = "Black";
    QString backgroundColor = "White";

    const QStringList colors = {
        "White", "Black","Red",
        "Dark red", "Green", "Dark green",
        "Blue", "Dark blue", "Cyan",
        "Dark cyan", "Magenta", "Dark magenta",
        "Yellow", "Dark yellow", "Gray",
        "Dark gray", "Light gray"
    };

    QLineEdit* fontSizeField;
    QComboBox* fontColorField;
    QComboBox* backgroundColorField;
};

#endif // __SETTINGS_MENU_H__
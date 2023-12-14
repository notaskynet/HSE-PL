#ifndef __MAINWINDOW_H__
#define __MAINWINDOW_H__

#include <QMainWindow>
#include <QMenuBar>
#include <QWidget>
#include <QTextEdit>
#include <QLabel>

#include "SettingsMenu.h"


class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow() = default;
protected slots:
    void updateFontSize();
    void updateFontColor();
    void updateBackgroundColor();
private:
    SettingsMenu* settings;
    QTextEdit*    textEdit;
};

#endif // __MAINWINDOW_H__
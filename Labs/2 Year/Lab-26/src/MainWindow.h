#ifndef __MAINWINDOW_H__
#define __MAINWINDOW_H__

#include <QMainWindow>
#include <QLineEdit>
#include <QMediaPlayer>
#include <QFileDialog>
#include <QPushButton>
#include <QWindow>
#include <QMenuBar>
#include <QAction>
#include <QVBoxLayout>

#define DEFAULT_WIDTH   640
#define DEFAULT_HEIGHT  480


class MainWindow: public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget* parent=nullptr);
    ~MainWindow()=default;
private:
    void selectFile();
    void exitProgram();
    void processMusic();
private:
    QMediaPlayer* player;
    QPushButton* control_button;
    QLineEdit* selected_file;
    QString filename = "";

    bool is_playing = false;
    bool is_file_selected = false;
};

#endif // __MAINWINDOW_H__
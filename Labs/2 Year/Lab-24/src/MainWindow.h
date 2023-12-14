#ifndef __MAIN_WINDOW_H__
#define __MAIN_WINDOW_H__

#include <QMainWindow>
#include <QWidget>
#include <QVBoxLayout>
#include <QFileDialog>
#include <QMenuBar>
#include <QMessageBox>

#include "ImageViewer.h"
#include "Server.h"


class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget* parent=nullptr);
protected:
    // Actions
    void startServer();
    void stopServer();
    void exitProgram();
    void showInformationAboutProgram();
    void openImage();
private:
    const int default_height = 480;
    const int default_width  = 640;

    ImageViewer* image_viewer;
    Server* server = nullptr;
};

#endif // __MAIN_WINDOW_H__
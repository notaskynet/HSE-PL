#include "MainWindow.h"



MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
{
    QWidget *ui_area = new QWidget;
    this->setCentralWidget(ui_area);

    this->setWindowTitle(tr("ImageViewer"));

    QVBoxLayout* layout = new QVBoxLayout(this);
    image_viewer = new ImageViewer;
    layout->addWidget(image_viewer);

    QAction* startServerAction = new QAction(tr("Запустить сервер"));
    connect(startServerAction, &QAction::triggered, this, &MainWindow::startServer);

    QAction* stopServerAction = new QAction(tr("Остановить сервер"));
    connect(stopServerAction, &QAction::triggered, this, &MainWindow::stopServer);
    
    QAction* openImageAction = new QAction(tr("Открыть изображение"));
    connect(openImageAction, &QAction::triggered, this, &MainWindow::openImage);

    QAction* exitProgramAction = new QAction(tr("Выход"));
    connect(exitProgramAction, &QAction::triggered, this, &MainWindow::exitProgram);

    QAction* showInfoAboutProgramAction = new QAction(tr("О программе"));
    connect(showInfoAboutProgramAction, &QAction::triggered, this, &MainWindow::showInformationAboutProgram);

    auto fileMenu = menuBar()->addMenu(tr("Файлы"));
    fileMenu->addAction(startServerAction);
    fileMenu->addAction(stopServerAction);
    fileMenu->addAction(openImageAction);
    fileMenu->addAction(exitProgramAction);

    auto helpMenu = menuBar()->addMenu(tr("Помощь"));
    helpMenu->addAction(showInfoAboutProgramAction);

    ui_area->setLayout(layout);
    this->resize(default_width, default_height);
}


void MainWindow::startServer()
{
    server = new Server(this);
}


void MainWindow::stopServer()
{
    if(server) delete server;
    server = nullptr;
}


void MainWindow::exitProgram()
{
    this->close();
}


void MainWindow::showInformationAboutProgram()
{
    QMessageBox msg;
    msg.setText("Автор: Даниил Спиридонов\nВерсия библиотеки Qt: 5.15");
    msg.exec();
}


void MainWindow::openImage()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Open Image"), "./", tr("Image Files (*.jpg)"));
    image_viewer->setImage(filename);
    if(server) server->setSendingFile(filename);
}


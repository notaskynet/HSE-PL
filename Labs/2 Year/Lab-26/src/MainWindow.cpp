#include "MainWindow.h"


MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
{
    QWidget* window = new QWidget;
    this->setCentralWidget(window);

    auto fileMenu = menuBar()->addMenu(tr("File"));

    QAction* select_file = new QAction("Select media file...");
    connect(select_file, &QAction::triggered, this, &MainWindow::selectFile);
    fileMenu->addAction(select_file);

    QAction* exit = new QAction("Exit");
    connect(exit, &QAction::triggered, this, &MainWindow::exitProgram);
    fileMenu->addAction(exit);

    player = new QMediaPlayer(this);

    control_button = new QPushButton;
    connect(control_button, &QPushButton::clicked, this, &MainWindow::processMusic);
    control_button->setEnabled(false);

    selected_file = new QLineEdit();
    selected_file->setReadOnly(true);
    selected_file->setText("Select file...");

    QVBoxLayout *layout = new QVBoxLayout(window);
    layout->addWidget(selected_file);
    layout->addWidget(control_button);
    
    this->resize(DEFAULT_WIDTH, DEFAULT_HEIGHT);
}


void MainWindow::selectFile()
{
    filename = QFileDialog::getOpenFileName(this, tr("Open Music"), "./", tr("Music Files (*.mp3)"));
    selected_file->setText(filename);
    QUrl file = QUrl::fromLocalFile(filename);
    player->setMedia(file);
    player->setVolume(50);

    if(!is_file_selected)
    {
        control_button->setEnabled(true);
        is_file_selected = true;
    }
}


void MainWindow::exitProgram()
{
    this->close();
}


void MainWindow::processMusic()
{
    if(is_playing)
    {
        control_button->setText("Play");
        player->pause();
    }
    else
    {
        control_button->setText("Stop");
        player->play();
    }
    is_playing = !is_playing;
    this->update();
}
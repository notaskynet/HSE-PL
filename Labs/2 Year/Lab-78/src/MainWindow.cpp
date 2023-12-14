#include "MainWindow.h"


MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
{
    this->setWindowTitle(tr("Notepad"));
    
    QTabWidget* tabs = new QTabWidget(this);
    this->setCentralWidget(tabs);

    settings = new SettingsMenu;
    textEdit = new QTextEdit;

    tabs->addTab(textEdit, "Editor");
    tabs->addTab(settings, "Settings");

    QAction* importSettingsAction = new QAction("Import settings");
    QAction* exportSettingsAction = new QAction("Export settings");

    auto fileMenu = menuBar()->addMenu(tr("File"));
    fileMenu->addAction(importSettingsAction);
    fileMenu->addAction(exportSettingsAction);

    connect(importSettingsAction, SIGNAL(triggered()), settings, SLOT(importXml()));
    connect(exportSettingsAction, SIGNAL(triggered()), settings, SLOT(exportXml()));

    connect(settings, SIGNAL(fontSizeChanged()), this, SLOT(updateFontSize()));
    connect(settings, SIGNAL(fontColorChanged()), this, SLOT(updateFontColor()));
    connect(settings, SIGNAL(backgroundColorChanged()), this, SLOT(updateBackgroundColor()));

    this->updateFontSize();
    this->updateFontColor();
    this->updateBackgroundColor();

    this->resize(640, 480);
}


void MainWindow::updateFontSize()
{
    QFont font = textEdit->currentFont();
    font.setPointSize(settings->getFontSize().toInt());
    textEdit->setFont(font);
    textEdit->update();
}


void MainWindow::updateFontColor()
{
    QString tmp = textEdit->toPlainText();
    textEdit->clear();
    textEdit->setTextColor(QColor(settings->getFontColor()));
    textEdit->insertPlainText(tmp);
    textEdit->update();

}


void MainWindow::updateBackgroundColor()
{
    QPalette p = textEdit->palette();
    p.setColor(QPalette::Base, settings->getBackgroundColor());
    textEdit->setPalette(p);
    textEdit->update();

}
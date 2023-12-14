#ifndef __MAINWINDOW_H__
#define __MAINWINDOW_H__

#include <QtGlobal>

#include <QTcpSocket>
#include <QApplication>

#include <QVBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QTextEdit>
#include <QWidget>


class MainWindow : public QWidget
{
    Q_OBJECT
public:
    MainWindow(QWidget* parent=nullptr);
private slots:
    void scan();
private:
    const quint16 end = 1024; // Upper bound of scanning range
    const quint16 timeout = 50; // timeout for scanning

    const int height = 480;
    const int width  = 640;

    QPushButton* start_scan;
    QLineEdit* addr_input;
    QTextEdit* port_info;

    QTcpSocket* m_socket;
};

#endif // __MAINWINDOW_H__
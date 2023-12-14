#include "MainWindow.h"


MainWindow::MainWindow(QWidget* parent)
    : QWidget(parent)
{
    this->setWindowTitle(tr("Port scanner"));
    this->setFixedSize(width, height);

    m_socket = new QTcpSocket(this);

    QVBoxLayout* main_layout = new QVBoxLayout(this);

    addr_input = new QLineEdit;
    addr_input->setPlaceholderText(tr("Введите сюда адрес"));
    main_layout->addWidget(addr_input);

    start_scan = new QPushButton(tr("Начать сканирование"));
    connect(start_scan, &QPushButton::clicked, this, &MainWindow::scan);
    main_layout->addWidget(start_scan);

    port_info = new QTextEdit;
    main_layout->addWidget(port_info);
    port_info->setPlaceholderText(tr("Здесь будет информация о портах..."));
    port_info->setReadOnly(true);
}


void MainWindow::scan()
{
    if(addr_input->text().isEmpty())
    {
        return;
    }

    port_info->clear();
    addr_input->setReadOnly(true);
    start_scan->setEnabled(false);

    port_info->append("Starting scan...");
    QString host = addr_input->text();
    for(quint16 port = 0; port < end; port++)
    {
        m_socket->connectToHost(host, port);
        bool is_connected = m_socket->waitForConnected(timeout);

        QString port_num = QString::number(port);
        if(is_connected)
        {   
            port_info->append("Порт " + port_num + ":\t открыт");
            m_socket->disconnectFromHost();
        }
        else
        {
            port_info->append("Порт " + port_num + ":\t закрыт");
        }
        qApp->processEvents(); // For responding of application
    }
    port_info->append("Сканирование завершено");

    addr_input->setReadOnly(false);
    start_scan->setEnabled(true);
}
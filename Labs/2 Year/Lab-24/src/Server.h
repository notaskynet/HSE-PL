#ifndef __SERVER_H__
#define __SERVER_H__

#include <QTcpServer>
#include <QTcpSocket>
#include <QWidget>
#include <QObject>
#include <QFile>

class Server : public QObject
{
    Q_OBJECT
public:
    Server(QWidget* parent=nullptr);
    ~Server();
    void setSendingFile(QString filename);
public slots:
    void handleNewConnection();
    void handleClient();
private:
    const int port = 31337;

    QTcpServer* m_server;
    bool is_listening;
    QMap<int,QTcpSocket*> SClients;

    QString m_filename = "";
};

#endif // __SERVER_H__
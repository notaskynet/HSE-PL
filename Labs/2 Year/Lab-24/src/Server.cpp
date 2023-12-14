#include "Server.h"


Server::Server(QWidget* parent)
{
    m_server = new QTcpServer(parent);
    connect(m_server, &QTcpServer::newConnection, this, &Server::handleNewConnection);
    if(m_server->listen(QHostAddress::Any, port) || is_listening)
    {
        is_listening = true;
        qDebug() << "Server started!";
    }
    else
    {
        qDebug() << "Unable to start the server";
    }
}


Server::~Server()
{
    if(is_listening)
    {
        foreach(int i, SClients.keys()) 
        {
            SClients[i]->close();
            SClients.remove(i);
        }
        m_server->close();
        is_listening = false;
    }
    delete m_server;
}


void Server::setSendingFile(QString filename)
{
    m_filename = filename;
}


void Server::handleNewConnection()
{
    if(is_listening)
    {
        QTcpSocket* client = m_server->nextPendingConnection();
        int idusersocs = client->socketDescriptor();
        SClients[idusersocs] = client;
        connect(SClients[idusersocs], &QTcpSocket::readyRead, this, &Server::handleClient);
    }
}


void Server::handleClient()
{
    QTcpSocket* client = (QTcpSocket*)sender();
    int idusersocs = client->socketDescriptor();

    QTextStream os(client);
    os.setAutoDetectUnicode(true);
    if(m_filename.isEmpty())
    {
        os << "HTTP/1.0 200 Ok\r\n"
           << "Content-Type: text/html; charset=\"utf-8\"\r\n"
           << "\r\n"
           << "<h1>Nothing to see here</h1>";
    }
    else
    {
        client->write(
            "HTTP/1.1 200 OK\r\n"
            "Content-Type: image/jpg; charset=\"utf-8\"\r\n"
            "\r\n"
        );

        QFile file(m_filename);
        file.open(QIODevice::ReadOnly);
        QByteArray file_data=file.readAll();
        client->write(file_data);
    }
    os << "\r\n\r\n";
    client->close();
    SClients.remove(idusersocs);
}
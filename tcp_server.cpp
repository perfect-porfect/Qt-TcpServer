// myserver.cpp
#include "tcp_server.h"

TCPServer::TCPServer(short port)
    : QTcpServer(nullptr), port_(port)
{
}

bool TCPServer::start()
{
    if(!this->listen(QHostAddress::Any, port_))
        return false;
    else
        return true;
}

void TCPServer::incomingConnection(qintptr socketDescriptor)
{
    qDebug() << "connection added: " << socketDescriptor;
    TCPClient *client = new TCPClient(socketDescriptor, this);
    connect(client, SIGNAL(finished()), client, SLOT(deleteLater()));
    client->start();
    emit new_connection(client);
}

void TCPServer::stop()
{

}

bool TCPServer::is_running()
{

}

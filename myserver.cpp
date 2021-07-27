// myserver.cpp

#include "myserver.h"
#include "mythread.h"

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

// This function is called by QTcpServer when a new connection is available.
void TCPServer::incomingConnection(qintptr socketDescriptor)
{
    // We have a new connection
    qDebug() << socketDescriptor << " Connecting...";

    // Every new connection will be run in a newly created thread
    TCPClient *thread = new TCPClient(socketDescriptor, this);

    // connect signal/slot
    // once a thread is not needed, it will be beleted later
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));

    thread->start();
}

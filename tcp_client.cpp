#include "tcp_client.h"
#include <QHostAddress>

TCPClient::TCPClient(qintptr ID, QObject *parent) :
    QThread(parent)
{
    this->socketDescriptor = ID;
}


qint16 TCPClient::get_port() const
{
    return port_;
}

QString TCPClient::get_ip()
{
    return ip_;
}

void TCPClient::run()
{
    // thread starts here
    qDebug() << " Thread started";

    socket_ = new QTcpSocket();

    // Set the ID
    if(!socket_->setSocketDescriptor(this->socketDescriptor))
    {
        // Something's wrong, we just emit a signal
        emit error(socket_->error());
        return;
    }

    ip_ = socket_->localAddress().toIPv4Address();
    port_ = socket_->localPort();

    // connect socket and signal
    // note - Qt::DirectConnection is used because it's multithreaded
    //        This makes the slot to be invoked immediately, when the signal is emitted.

//    connect(socket_, SIGNAL(readyRead()), this, SLOT(readyRead()), Qt::DirectConnection);
//    connect(socket_, SIGNAL(disconnected()), this, SLOT(disconnected()));

    // We'll have multiple clients, we want to know which is which
//    qDebug() << socketDescriptor << " Client connected";

    // make this thread a loop,
    // thread will stay alive so that signal/slot to function properly
    // not dropped out in the middle when thread dies

    exec();
}

//void TCPClient::readyRead()
//{
//    // get the information
////    QByteArray Data = socket_->readAll();

////    // will write on server side window
////    qDebug() << socketDescriptor << " Data in: " << Data;

////    socket_->write(Data);
//}

//void TCPClient::disconnected()
//{
//    qDebug() << socketDescriptor << " Disconnected";


//    socket_->deleteLater();
//    exit(0);
//}

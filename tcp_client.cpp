#include "tcp_client.h"
#include <QHostAddress>

TCPClient::TCPClient(qintptr ID, QObject *parent) :
    QThread(parent)
{
    is_socket_connected_from_server_ = true;
    this->socketDescriptor = ID;
}

TCPClient::TCPClient(QString ip, qint16 port, QObject *parent)
    :QThread(parent), ip_(ip), port_(port)
{
    is_socket_connected_from_server_ = false;
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
    socket_ = new QTcpSocket();
    if (is_socket_connected_from_server_)  {
        if(!socket_->setSocketDescriptor(this->socketDescriptor)) {
            emit error(socket_->error());
            return;
        }
    } else {
        socket_->connectToHost(ip_, port_);
        if(!socket_->waitForConnected(5000)) {
            emit error(socket_->error());
            return;
        }
    }

    ip_ = socket_->localAddress().toIPv4Address();
    port_ = socket_->localPort();
    connect(socket_, &QTcpSocket::readyRead, this, &TCPClient::ready_read, Qt::DirectConnection);
    connect(socket_, &QTcpSocket::disconnected, this, &TCPClient::disconnected);

    exec();
}

int TCPClient::send(const QByteArray& data)
{
    return socket_->write(data);
    // socket_->flush();
    // socket_->waitForBytesWritten(3000);
}

void TCPClient::ready_read()
{
    QByteArray Data = socket_->readAll();
    emit data_received(Data);
}

void TCPClient::disconnected()
{
    emit disconnect();
    socket_->deleteLater();
}

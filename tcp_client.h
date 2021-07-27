#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QThread>
#include <QTcpSocket>
#include <QDebug>

class TCPClient : public QThread
{
    Q_OBJECT
public:
    explicit TCPClient(qintptr ID, QObject *parent = 0);
    explicit TCPClient(QString ip, qint16 port, QObject * parent = 0);
    qint16 get_port() const;
    QString get_ip();
    void run();
    int send(const QByteArray &data);
private slots:
    void ready_read();
    void disconnected();
signals:
    void error(QTcpSocket::SocketError socketerror);
    void data_received(QByteArray& data);
    void disconnect();
private:
    QString ip_;
    qint16 port_;
    QTcpSocket *socket_;
    qintptr socketDescriptor;
    bool is_socket_connected_from_server_;
};

#endif // MYTHREAD_H

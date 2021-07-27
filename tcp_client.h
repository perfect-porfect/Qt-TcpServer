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
    qint16 get_port() const;
    QString get_ip();
    void run();

signals:
    void error(QTcpSocket::SocketError socketerror);

private:
    qint16 port_;
    QString ip_;
    QTcpSocket *socket_;
    qintptr socketDescriptor;
};

#endif // MYTHREAD_H

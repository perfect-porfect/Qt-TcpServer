// myserver.h

#ifndef MYSERVER_H
#define MYSERVER_H

#include <QTcpServer>

class TCPServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit TCPServer(short port);
    bool start();
    void stop();
    bool is_running();

private:
    short port_;


signals:
    void new_connection();

protected:
    void incomingConnection(qintptr socketDescriptor);

};

#endif // MYSERVER_H

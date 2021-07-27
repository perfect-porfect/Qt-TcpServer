#include <QCoreApplication>
#include <thread>
#include <iostream>

#include "tcp_server.h"

#define SERVER_PORT (8585)

void data_received(QByteArray& data)
{
    std::cout << "receive " << data.size() << " bytes" << std::endl;
}

void disconnect()
{
    std::cout << "disconnect" << std::endl;
}

void new_connection(TCPClient* client)
{
    qDebug() << client->get_ip() << " " << client->get_port();
    QObject::connect(client, &TCPClient::data_received, data_received);
    QObject::connect(client, &TCPClient::disconnect, disconnect);
}


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // Make a server and starts it
    TCPServer server(SERVER_PORT);
    QObject::connect(&server, &TCPServer::new_connection, new_connection);
    bool ret = server.start();
    if (ret)
        std::cout << "start tcp_server with port " << SERVER_PORT << std::endl;
    else
        std::cout << "Cant start tcp server" << SERVER_PORT << std::endl;

//    while(1) {
//        std::this_thread::sleep_for(std::chrono::seconds(10));
////        break;
//    }

    return a.exec();
}

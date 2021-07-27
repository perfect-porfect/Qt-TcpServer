#include <QCoreApplication>
#include <thread>

#include "myserver.h"

int main(int argc, char *argv[])
{
//    QCoreApplication a(argc, argv);

    // Make a server and starts it
    TCPServer server(1234);
    server.start();

    while(1) {
        std::this_thread::sleep_for(std::chrono::seconds(10));
        break;
    }

//    return a.exec();
}

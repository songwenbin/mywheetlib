#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "EventWait.h"
#include "EventManager.h"
#include "Thread.h"
#include "EventServerSocket.h"
#include "NetWorkAddress.h"


class Test
{
public:
    void doit()
    {
        printf("new connnection\n");
    }
};

int main()
{
    //1 . create manager
    EventManager evManager;

    //2. create server socket
    NetWorkAddress addr(5258);
    EventServerSocket serverSocket(addr);
    Test t;
    serverSocket.setActionAfterConn(boost::bind(&Test::doit, t));
    
    //3. create server event
    Event ev(&evManager, serverSocket.fd());
    ev.setReadEvent(boost::bind(&EventServerSocket::handleRead,
                             serverSocket)); 
    evManager.appendEvent(&ev);

    //4. start server loop and listen server event
    serverSocket.listenConnection();
    evManager.startEventLoop();

    return 0;
}

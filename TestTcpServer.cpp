#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "EventTcpServer.h"

class Test
{
public:
    void doit() 
    { printf("ok\n"); }
};

int main()
{
    EventTcpServer tcpServ;

    Test t;

    tcpServ.setMessageCb(boost::bind(&Test::doit, t));

   
    tcpServ.startServer(5258);
    tcpServ.startLoop();

    return 0;
}

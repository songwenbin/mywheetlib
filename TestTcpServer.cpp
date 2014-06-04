#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "EventTcpServer.h"
#include "EventBuffer.h"

class Test
{
public:
    void doit(EventBuffer * buf) 
    { printf("%s\n", buf->peek()); }
};

int main()
{
    EventTcpServer tcpServ;

    Test t;

    tcpServ.setMessageCb(boost::bind(&Test::doit, t, _1));
   
    tcpServ.startServer(5258);
    tcpServ.startLoop();

    return 0;
}

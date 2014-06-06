#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "EventTcpServer.h"
#include "EventBuffer.h"
#include "TcpConnection.h"

// Echo Server
void doit(TcpConnPtr conn, EventBuffer * buf) 
{ 
    char * str = buf->getStr();
    buf->popData(strlen(str));

    printf("%s\n", str); 
    std::string data(str);
    conn->sendData(data);
}

int main()
{
    EventTcpServer tcpServ;

    tcpServ.setMessageCb(doit);
   
    tcpServ.startServer(5258);
    tcpServ.startLoop();

    return 0;
}

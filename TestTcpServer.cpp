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

void doit(TcpConnPtr conn, EventBuffer * buf) 
{ 
    printf("%s\n", buf->peek()); 
    std::string data("ok");
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

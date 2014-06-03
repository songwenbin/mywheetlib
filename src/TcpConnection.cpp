#include "TcpConnection.h"
#include <stdio.h>

void TcpConnection::handleRead()
{
    // 1. read socket data
    char buf[65536];
    ssize_t n = read(fd_, buf, sizeof buf);
    // 2. callback user infomation
    if(messageCb_)
    {
        messageCb_();
    }
}

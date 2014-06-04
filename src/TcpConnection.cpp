#include "TcpConnection.h"
#include <stdio.h>

void TcpConnection::handleRead()
{
    ssize_t n = buffer_.Read(fd_);
    if(n > 0)
    {
        if(messageCb_)
        {
            messageCb_(&buffer_);
        }
    }
    else if(n == 0)
    {
        closeCb_(fd_);
    }
    else
    {

    }
}

#include "TcpConnection.h"
#include <stdio.h>

void TcpConnection::handleRead()
{
    ssize_t n = buffer_.Read(fd_);
    if(n > 0)
    {
        if(messageCb_)
        {
            messageCb_(this, &buffer_);
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

void TcpConnection::handleWrite()
{
    printf("......................\n");
    /*
    if(outBuffer_.dataSize() > 0)
    {
        ssize_t n = write(fd_, outBuffer_.peek(), outBuffer_.dataSize());
        // - n
    }
    else if(outBuffer_.dataSize() == 0)
    {
        mg_->removeWriteEvent(fd_);
    }
    */
    mg_->removeWriteEvent(fd_);
}

void TcpConnection::sendData(std::string & data)
{
    mg_->appendWriteEvent(fd_);
    //printf("test %d\n", mg_->appendWriteEvent(fd_));
}

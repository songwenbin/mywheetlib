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
    if(outBuffer_.dataSize() > 0)
    {
        ssize_t n = write(fd_, outBuffer_.peek(), outBuffer_.dataSize());
        outBuffer_.retrieve(n);
    }
    else if(outBuffer_.dataSize() == 0)
    {
        mg_->removeWriteEvent(fd_);
    }
}

void TcpConnection::sendData(std::string & data)
{
    outBuffer_.append(data.c_str(), data.size());
    mg_->appendWriteEvent(fd_);
}

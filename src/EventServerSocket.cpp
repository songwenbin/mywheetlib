#include "EventServerSocket.h"
#include "Sockets.h"
#include <stdio.h>

EventServerSocket::EventServerSocket(NetWorkAddress & listen)
    :acceptFd_(socketCreate())
{
    socketBind(acceptFd_, listen.getSocketAddressInet());
}

EventServerSocket::~EventServerSocket()
{
    //socketClose(acceptFd_);
}

void EventServerSocket::listenConnection()
{
    socketListen(acceptFd_);
}

void EventServerSocket::handleRead()
{
    NetWorkAddress peerAddress(0);
    int connfd = socketAccept(acceptFd_, &peerAddress.getSocketAddressInet());
    if(connfd >= 0)
    {
        if(actionAfterConnection_)
        {
            actionAfterConnection_(connfd, peerAddress);
        }
    }
    else
    {
        socketClose(connfd);
    }
}

#include "EventTcpServer.h"
#include <stdio.h>

EventTcpServer::EventTcpServer()
{
}

EventTcpServer::~EventTcpServer()
{
    if(serversocket_ != NULL)
    {
        delete serversocket_; 
        serversocket_ = NULL;
    }
}

void EventTcpServer::setMessageCb(const CallBack & cb)
{ messageCb_ = cb; } 

void EventTcpServer::startServer(int port) 
{
    NetWorkAddress addr(5258);
    serversocket_ = new EventServerSocket(addr);
    serversocket_->setActionAfterConn(boost::bind(&EventTcpServer::doConnection, this, _1, _2)); 

    tcpEvent = new Event(&evManager_, serversocket_->fd());
    tcpEvent->setReadEvent(boost::bind(&EventServerSocket::handleRead, serversocket_));
    evManager_.appendEvent(tcpEvent);

    serversocket_->listenConnection();
}

void EventTcpServer::startLoop()
{
    while(1)
    {
        evManager_.startEventLoop();
    }
}

void EventTcpServer::doConnection(int fd, NetWorkAddress & peer)
{
    // 1. new tcp connection
    TcpConnection * conn = new TcpConnection(fd, new Event(&evManager_, fd));
    conn->setMessageCb(messageCb_);
    conn->setCloseConnCb(boost::bind(&EventTcpServer::removeConnection, this, _1));
        
    // 2. create event and append event
    (conn->event())->setReadEvent(boost::bind(&TcpConnection::handleRead, conn));
    (conn->event())->setCloseEvent(boost::bind(&EventTcpServer::removeConnection, this, _1));
    evManager_.appendEvent(conn->event());

    // 3. add tcp server management
    printf("recieve a connnection\n");
}

void EventTcpServer::removeConnection(int fd)
{
    evManager_.removeEvent(fd); 
}

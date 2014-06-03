#ifndef _EVENT_TCP_SERVER_HEADER_
#define _EVENT_TCP_SERVER_HEADER_

#include <boost/function.hpp>
#include <boost/bind.hpp>
#include "EventManager.h"
#include "EventServerSocket.h"
#include "NetWorkAddress.h"
#include "TcpConnection.h"

class EventTcpServer
{
public:
    typedef boost::function<void()> CallBack;

    EventTcpServer();
    ~EventTcpServer();

    void setMessageCb(const CallBack & cb);

    void startServer(int port);

    void startLoop();

    void doConnection(int fd, NetWorkAddress & peer);

    void removeConnection(int fd);

private:
    EventServerSocket *serversocket_;
    EventManager   evManager_;
    Event          *tcpEvent;

    CallBack messageCb_;
};

#endif

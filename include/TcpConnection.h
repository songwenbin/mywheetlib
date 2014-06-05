#ifndef _TCP_CONNECTION_HEADER
#define _TCP_CONNECTION_HEADER

#include <vector>
#include <unistd.h>
#include <boost/function.hpp>
#include "Event.h"
#include "EventBuffer.h"
#include "EventManager.h"

class TcpConnection;

typedef TcpConnection * TcpConnPtr;

class TcpConnection
{
public:
    typedef boost::function<void(TcpConnPtr conn, EventBuffer * buf)> MessageCallBack;
    typedef boost::function<void(int)> CallBack1;

    TcpConnection(int fd, Event * event, EventManager *mg)
        :fd_(fd),
         event_(event),
         mg_(mg) 
    {}

    ~TcpConnection(){close(fd_);}

    void setMessageCb(const MessageCallBack & cb)
    { messageCb_ = cb; }

    void setCloseConnCb(const CallBack1 &cb) 
    { closeCb_ = cb; }

    Event * event()
    { return event_; }

    void handleRead();
    void handleWrite();
    void sendData(std::string & data);
    
private:
    int fd_;
    MessageCallBack messageCb_; 
    CallBack1 closeCb_;
    
    Event * event_;

    EventBuffer buffer_;
    EventBuffer outBuffer_;
 
    EventManager * mg_;
};

#endif

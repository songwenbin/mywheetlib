#ifndef _TCP_CONNECTION_HEADER
#define _TCP_CONNECTION_HEADER

#include <unistd.h>
#include <boost/function.hpp>
#include "Event.h"

class TcpConnection
{
public:
    typedef boost::function<void()> CallBack;

    TcpConnection(int fd, Event * event)
        :fd_(fd),
         event_(event)
    {}

    ~TcpConnection(){close(fd_);}

    void setMessageCb(CallBack & cb)
    { messageCb_ = cb; }

    Event * event()
    { return event_; }

    void handleRead();
private:
    int fd_;
    CallBack messageCb_; 
    
    Event * event_;
};

#endif

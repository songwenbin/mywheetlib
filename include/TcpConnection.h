#ifndef _TCP_CONNECTION_HEADER
#define _TCP_CONNECTION_HEADER

#include <unistd.h>
#include <boost/function.hpp>
#include "Event.h"

class TcpConnection
{
public:
    typedef boost::function<void()> CallBack;
    typedef boost::function<void(int)> CallBack1;

    TcpConnection(int fd, Event * event)
        :fd_(fd),
         event_(event)
    {}

    ~TcpConnection(){close(fd_);}

    void setMessageCb(const CallBack & cb)
    { messageCb_ = cb; }

    void setCloseConnCb(const CallBack1 &cb) 
    { closeCb_ = cb; }

    Event * event()
    { return event_; }

    void handleRead();
    
    //void handleClose();
private:
    int fd_;
    CallBack messageCb_; 
    CallBack1 closeCb_;
    
    Event * event_;
};

#endif

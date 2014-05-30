#ifndef _EVENT_HEADER_
#define _EVENT_HEADER_

#include <boost/function.hpp>

class Event
{
public:
    typedef boost::function<void()> CallBack;

    Event():fd_(0),type_(NoneEvent){}
    Event(int fd):fd_(fd){}
    ~Event(){}

    void setFd(int fd){fd_ = fd;}
    void setType(int type){type_ = type;}

    int  fd() { return fd_; }

    void handleEvent();
   
    void setReadEvent(const CallBack & cb)
    {
        readCb_ = cb;
    }

    void setWriteEvent(const CallBack & cb)
    {
        writeCb_ = cb;
    }

    void setCloseEvent(const CallBack & cb)
    {
        closeCb_ = cb;
    }
    
private:
    static const int NoneEvent;
    static const int ReadEvent;
    static const int WriteEvent;

    int fd_;
    int type_; 

    CallBack readCb_;
    CallBack writeCb_;
    CallBack closeCb_;
};

#endif //_EVENT_HEADER_

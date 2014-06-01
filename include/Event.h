#ifndef _EVENT_HEADER_
#define _EVENT_HEADER_

#include <boost/function.hpp>

class EventManager;

class Event
{
public:
    static const int NoneEvent;
    static const int ReadEvent;
    static const int WriteEvent;

    typedef boost::function<void()> CallBack;

    Event(int fd, int type)
        :type_(type), 
         fd_(fd){}

    Event(EventManager * eManager, int fd)
         :eManager_(eManager),
          type_(NoneEvent),
          fd_(fd)
    {
    }
         
    ~Event(){}

    void setFd(int fd){fd_ = fd;}
    void setType(int type){type_ = type;}

    int  fd() { return fd_; }
    int  type() {return type_;}

    void handleReadEvent();
    void handleWriteEvent();
   
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
    int fd_;
    int type_; 
    
    EventManager * eManager_;

    CallBack readCb_;
    CallBack writeCb_;
    CallBack closeCb_;
};

#endif //_EVENT_HEADER_

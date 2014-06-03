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
    static const int CloseEvent;

    typedef boost::function<void()> CallBack;
    typedef boost::function<void(int)> CallBack1;

    Event(int fd, int type)
        :type_(type), 
         fd_(fd){
        readCb_ = NULL;
    }

    Event(EventManager * eManager, int fd)
         :eManager_(eManager),
          type_(NoneEvent),
          fd_(fd)
    {
        readCb_ = NULL;
    }
         
    ~Event(){}

    void setFd(int fd){fd_ = fd;}
    void setType(int type){type_ = type;}

    int  fd() { return fd_; }
    int  type() {return type_;}

    void handleReadEvent();
    void handleWriteEvent();
    void handleCloseEvent(int fd);
   
    void setReadEvent(const CallBack & cb)
    {
        readCb_ = cb;
    }

    void setWriteEvent(const CallBack & cb)
    {
        writeCb_ = cb;
    }

    void setCloseEvent(const CallBack1 & cb)
    {
        closeCb_ = cb;
    }
    
private:
    int fd_;
    int type_; 
    
    EventManager * eManager_;

    CallBack readCb_;
    CallBack writeCb_;
    CallBack1 closeCb_;
};

#endif //_EVENT_HEADER_

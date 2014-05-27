#ifndef _EVENT_HEADER_
#define _EVENT_HEADER_

class Event
{
public:
    Event():fd_(0),type_(NoneEvent){}
    ~Event(){}

    void setFd(int fd){fd_ = fd;}
    void setType(int type){type_ = type;}
    
    int fd_;
private:
    static const int NoneEvent;
    static const int ReadEvent;
    static const int WriteEvent;

    int type_; 
};

#endif //_EVENT_HEADER_

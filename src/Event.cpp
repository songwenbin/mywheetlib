#include "Event.h"
#include <sys/epoll.h>

const int Event::NoneEvent  = 0;
const int Event::ReadEvent  = EPOLLIN | EPOLLPRI;
const int Event::WriteEvent = EPOLLOUT;


void Event::handleEvent()
{
    if(type_ == NoneEvent)
    {

    }
    else if(type_ == ReadEvent)
    {
        if(readCb_) readCb_();        
    }
    else if(type_ == WriteEvent)
    {

    }
}

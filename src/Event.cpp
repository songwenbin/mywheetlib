#include "Event.h"
#include <sys/epoll.h>
#include <stdio.h>

const int Event::NoneEvent  = 0;
const int Event::ReadEvent  = EPOLLIN | EPOLLPRI;
const int Event::WriteEvent = EPOLLOUT;
const int Event::CloseEvent = EPOLLHUP;


void Event::handleReadEvent()
{
    if(readCb_) 
    {
        readCb_();        
    }
}

void Event::handleWriteEvent()
{
    if(writeCb_)
    {
        writeCb_();
    }
}

void Event::handleCloseEvent(int fd)
{
    if(closeCb_)
    {
        closeCb_(fd);
    }
}

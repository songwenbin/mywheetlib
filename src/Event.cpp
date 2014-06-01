#include "Event.h"
#include <sys/epoll.h>
#include <stdio.h>

const int Event::NoneEvent  = 0;
const int Event::ReadEvent  = EPOLLIN | EPOLLPRI;
const int Event::WriteEvent = EPOLLOUT;


void Event::handleReadEvent()
{
    if(readCb_) 
    {
        readCb_();        
    }
}

void Event::handleWriteEvent()
{

}


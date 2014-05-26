#include "EventWait.h"
#include <stdio.h>

EventWait::EventWait()
    :efd_(epoll_create(MAXEVENT)),
     events_(MAXEVENT)
{
}

EventWait::~EventWait()
{
}

std::vector<Event> EventWait::waitEvent()
{
    std::vector<Event> events;

    int nfds = epoll_wait(efd_, 
                          &*events_.begin(), 
                          static_cast<int>(events_.size()), 
                          -1);

    if(nfds == -1) 
    {
        return events;
    }

    for(std::vector<struct epoll_event>::iterator iter = events_.begin(); iter != events_.end();
        iter ++)
    {
        Event ev;
        ev.setFd((*(iter)).data.fd);     
        ev.setType((*(iter)).events);
    
        events.push_back(ev);
    }

    return events;
}


int EventWait::appendReadEvent(int fd)
{
    if(fd <= 0)
    {
        return -1;
    }

    struct epoll_event ev;
    ev.events  = EPOLLIN; 
    ev.data.fd = fd; 

    if(epoll_ctl(efd_, EPOLL_CTL_ADD, fd, &ev) == -1) 
    {
        return -2;
    }

    return 0;
}

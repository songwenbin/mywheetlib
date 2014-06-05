#include "EventWait.h"
#include <stdio.h>
#include <unistd.h>

EventWait::EventWait()
    :efd_(epoll_create(MAXEVENT)),
     events_(MAXEVENT)
{
}

EventWait::~EventWait()
{
    close(efd_);
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

    for(std::vector<struct epoll_event>::iterator iter = events_.begin(); iter != events_.end(); iter ++)
    {
        int fd   = (*(iter)).data.fd;
        int type = (*(iter)).events;

        Event ev(fd, type);
        ev.setType(type);
        events.push_back(ev);
    }

    return events;
}

int EventWait::appendEvent(int fd, int type)
{
    if(fd <= 0)
    {
        return -1;
    }

    struct epoll_event ev;
    bzero(&ev, sizeof ev);
    ev.events  = type; 
    ev.data.fd = fd; 

    if(epoll_ctl(efd_, EPOLL_CTL_ADD, fd, &ev) == -1) 
    {
        if(epoll_ctl(efd_, EPOLL_CTL_MOD, fd, &ev) == -1) 
        {
             return -2;
        }
    }

    return 0;
}

int EventWait::updateEvent(int fd, int type)
{
    if(fd <= 0)
    {
        return -1;
    }

    struct epoll_event ev;
    bzero(&ev, sizeof ev);
    ev.events = type;
    ev.data.fd = fd;

    if(epoll_ctl(efd_, EPOLL_CTL_MOD, fd, &ev) < 0)
    {
        return -2;
    }

    return 0;
}

int EventWait::removeEvent(int fd)
{
    struct epoll_event ev;
    bzero(&ev, sizeof ev);
    ev.events = Event::NoneEvent;
    ev.data.fd = fd;

    if(epoll_ctl(efd_, EPOLL_CTL_MOD, fd, &ev) < 0)
    {
        fprintf(stderr, "remove event is error!");
    }
}

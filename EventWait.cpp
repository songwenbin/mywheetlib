#include "EventWait.h"

std::vector<Event> EventWait::waitEvent()
{
    std::vector<Event> events;

    int nfds = epoll_wait(efd_, 
                          &*events_.begin(), 
                          static_cast<int>(events_.size()), 
                          1);

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

EventWait::~EventWait()
{
}

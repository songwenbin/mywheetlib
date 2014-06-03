#include "EventManager.h"
#include <assert.h>
#include <vector>
#include <stdio.h>

//ToDo need ReadWriteLock For eventList_

int EventManager::handleEvents(int fd, int type)
{
     EventMap::const_iterator evIndex = eventList_.find(fd);
     if(evIndex == eventList_.end())
     {
         return -1;
     }

     Event * ev = evIndex->second;

     if(type & Event::NoneEvent)
     {

     }
     else if(type & Event::ReadEvent)
     {
         ev->handleReadEvent();
     }
     else if(type & Event::WriteEvent)
     {

     }
     else if(!(type & Event::ReadEvent) &&
              (type & Event::CloseEvent))
     {
         ev->handleCloseEvent(fd);
     }

     return 0;
}

int EventManager::appendEvent(Event * ev)
{
    int fd = ev->fd();
    eventList_[fd] = ev;

    //epoll event
    loop_.appendReadEvent(ev->fd());
}

int EventManager::removeEvent(int fd)
{
    //epoll event
    loop_.removeEvent(fd, eventList_[fd]->type());

    assert(eventList_.find(fd) != eventList_.end());
    eventList_.erase(eventList_.find(fd));
    
}

void EventManager::startEventLoop()
{
    std::vector<Event> events = loop_.waitEvent();
    for(std::vector<Event>::iterator iter = events.begin();
        events.end() != iter;
        ++ iter)
    {
        handleEvents((*iter).fd(), (*iter).type()); 
    }
}

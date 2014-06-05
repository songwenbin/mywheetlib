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
         ev->handleWriteEvent();
     }
     else if(!(type & Event::ReadEvent) &&
              (type & Event::CloseEvent))
     {
         ev->handleCloseEvent(fd);
     }

     return 0;
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

int EventManager::appendReadEvent(Event * ev)
{
    //1. add event map
    int fd = ev->fd();
    int type = ev->type() | Event::ReadEvent;
    ev->setType(type);
    eventList_[fd] = ev;

    //2. add epoll wait
    loop_.appendEvent(fd, type);
}

int EventManager::removeReadEvent(int fd)
{
    //1. remove epoll wait
    Event * ev = eventList_[fd]; 
    int type = ev->type() & (~Event::ReadEvent);
    loop_.updateEvent(fd, type);
}

int EventManager::appendWriteEvent(int fd)
{
    //1. add event map
    Event * ev = eventList_[fd]; 
    int type = ev->type() | Event::WriteEvent;

    //2. add epoll wait
    loop_.updateEvent(fd, type);
}

int EventManager::removeWriteEvent(int fd)
{
    //1. remove epoll wait
    Event * ev = eventList_[fd]; 
    int type = ev->type() & (~Event::WriteEvent);
    loop_.updateEvent(fd, type);
}


int EventManager::removeEvent(int fd)
{
    //1. remove epoll wait 
    loop_.removeEvent(fd);

    //2. remove event map
    assert(eventList_.find(fd) != eventList_.end());
    eventList_.erase(eventList_.find(fd));
}

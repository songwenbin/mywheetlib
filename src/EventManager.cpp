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
     /*
     std::vector<int> fds = ev->handleEvent();

     for(std::vector<int>::iterator it = fds.begin(); 
         fds.end() != it;
         it ++)
     {
          removeEvent(*it);
     }
     */

     return 0;
}

int EventManager::appendEvent(Event * ev)
{
    int fd = ev->fd();
    eventList_[fd] = ev;

    loop_.appendReadEvent(ev->fd());
}

int EventManager::removeEvent(int fd)
{
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

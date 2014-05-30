#include "EventManager.h"
#include <assert.h>
#include <vector>

//ToDo need ReadWriteLock For eventList_

int EventManager::handleEvents(int fd)
{
     EventMap::const_iterator evIndex = eventList_.find(fd);
     if(evIndex == eventList_.end())
     {
         return -1;
     }

     Event * ev = evIndex->second;
     ev->handleEvent();
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
}

int EventManager::removeEvent(int fd)
{
    assert(eventList_.find(fd) != eventList_.end());
    eventList_.erase(eventList_.find(fd));
}

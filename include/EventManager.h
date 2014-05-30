#ifndef _EVENT_MANAGER_HEADER_
#define _EVENT_MANAGER_HEADER_

#include "Event.h"
#include <map>

class EventManager
{
public:
    int appendEvent(Event * ev);
    int removeEvent(int fd);

    int handleEvents(int fd);
private:
    typedef std::map<int, Event*> EventMap;

    EventMap eventList_;
};

#endif

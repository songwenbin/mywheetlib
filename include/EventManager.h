#ifndef _EVENT_MANAGER_HEADER_
#define _EVENT_MANAGER_HEADER_

#include "Event.h"
#include "EventWait.h"
#include <map>


class EventManager
{
public:
    int appendEvent(Event * ev);
    int removeEvent(int fd);

    void startEventLoop();
private:
    int handleEvents(int fd,int type);

private:
    typedef std::map<int, Event*> EventMap;

    EventMap eventList_;

    EventWait loop_;
};

#endif

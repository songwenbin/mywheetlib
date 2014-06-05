#ifndef _EVENT_MANAGER_HEADER_
#define _EVENT_MANAGER_HEADER_

#include "Event.h"
#include "EventWait.h"
#include <map>


class EventManager
{
public:
    int appendEvent(Event * ev);//
    int removeEvent(int fd);//

    void startEventLoop();

    int handleEvents(int fd,int type);

    int appendReadEvent(Event * ev);
    int removeReadEvent(int fd);
    int appendWriteEvent(int fd);
    int removeWriteEvent(int fd);

private:
    typedef std::map<int, Event*> EventMap;

    EventMap eventList_; // eventList_[fd] = Event

    EventWait loop_;
};

#endif

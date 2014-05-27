#ifndef _EVENT_TIMER_HEADER_
#define _EVENT_TIMER_HEADER_

#include <sys/timerfd.h>

class EventTimer
{
public:
    EventTimer();
    ~EventTimer();

    int  fd(); 
    void setTimeS(int second);

private:
    int fd_;
    struct itimerspec howlong;
};

#endif

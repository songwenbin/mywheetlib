#include "EventTimer.h"
#include <string.h>
#include <unistd.h>

EventTimer::EventTimer()
    :fd_(timerfd_create(CLOCK_MONOTONIC, TFD_NONBLOCK|TFD_CLOEXEC))
{
    bzero(&howlong, sizeof howlong);
}

EventTimer::~EventTimer()
{
    close(fd_);
}

int EventTimer::fd()
{
    return fd_;
}

void EventTimer::setTimeS(int second)
{
    howlong.it_value.tv_sec = second;
    timerfd_settime(fd_, 0, &howlong, NULL);
}

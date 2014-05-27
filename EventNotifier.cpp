#include "EventNotifier.h"
#include <sys/eventfd.h>
#include <unistd.h>

EventNotifier::EventNotifier()
    :fd_(eventfd(0, EFD_CLOEXEC|EFD_NONBLOCK))
{

}

EventNotifier::~EventNotifier()
{
    close(fd_);
}

int EventNotifier::fd()
{
    return fd_;
}

int EventNotifier::Notify()
{
    uint64_t u = 1;
    ssize_t  s = write(fd_, &u, sizeof(uint64_t));
    if(s != sizeof(uint64_t))
    {
        return -1;
    }

    return 0;
}


#ifndef _EVENT_NOTIFIER_HEADER_
#define _EVENT_NOTIFIER_HEADER_

class EventNotifier
{
public:
    EventNotifier();
    ~EventNotifier();

    int fd();
    int Notify();

private:
    int fd_;
};

#endif

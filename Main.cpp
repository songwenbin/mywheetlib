#include "EventWait.h"
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/timerfd.h>

#include "EventTimer.h"
#include "EventNotifier.h"
#include "EventManager.h"
#include "Thread.h"


class Foo
{
public:
    void test()
    {
        sleep(2);
        printf("test\n");
        note_->Notify();
    }

    void setNote(EventNotifier * note)
    {
        note_ = note;
    }
private:
    EventNotifier * note_;
};

void test()
{
    printf("test");
}


int main()
{
    EventManager evManager;
    EventWait loop;

    EventTimer time;
    time.setTimeS(5); 
    loop.appendReadEvent(time.fd());

    EventNotifier note;
    loop.appendReadEvent(note.fd());
    
    Event ev(note.fd());
    ev.setReadEvent(test);
    evManager.appendEvent(&ev);

    Foo foo;
    foo.setNote(&note);
    Thread t(boost::bind(&Foo::test, foo));
    t.start();
    

    std::vector<Event> events = loop.waitEvent();
    for(std::vector<Event>::iterator iter = events.begin(); 
        iter != events.end();
        iter ++)
    {
        evManager.handleEvents((*iter).fd());
    }
    printf("%d\n", events.size());
    t.join();

    return 0;
}

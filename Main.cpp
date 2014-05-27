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
#include "Thread.h"


class Foo
{
public:
    void test()
    {
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



int main()
{
    EventWait loop;

    EventTimer time;
    time.setTimeS(5); 
    loop.appendReadEvent(time.fd());

    EventNotifier note;
    loop.appendReadEvent(note.fd());

    Foo foo;
    foo.setNote(&note);
    Thread t(boost::bind(&Foo::test, foo));
    t.start();
    
    std::vector<Event> events = loop.waitEvent();
    printf("%d\n", events.size());
    t.join();

    return 0;
}

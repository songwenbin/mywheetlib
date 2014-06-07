#ifndef _CONDITION_HEADER_
#define _CONDITION_HEADER_

#include "Mutex.h"

class Condition
{
public:
    Condition(MutexLock & mutex)
        :mutex_(mutex_)
    {
        pthread_cond_init(&cond_, NULL);
    }
    ~Condition()
    {
        pthread_cond_destroy(&cond_);
    }

    void wait()
    {
        pthread_cond_wait(&cond_, mutex_.getMutex());   
    }

    void notify()
    {
        pthread_cond_signal(&cond_);
    }

    void notifyAll()
    {
        pthread_cond_broadcast(&cond_);
    }

private:
    MutexLock &    mutex_;
    pthread_cond_t cond_;
};

#endif

#ifndef _MUTEX_HEADER_
#define _MUTEX_HEADER_

#include <pthread.h>

class MutexLock
{
public:
    MutexLock()
    {
        pthread_mutex_init(&mutex_, NULL);
    }

    ~MutexLock()
    {
        pthread_mutex_destroy(&mutex_);
    }

    void lock()
    {
        pthread_mutex_lock(&mutex_);
    }

    void unlock()
    {
        pthread_mutex_unlock(&mutex_);
    }

    pthread_mutex_t * getMutex()
    {
        return &mutex_;
    }

private:
    pthread_mutex_t mutex_;
};

class MutexLockGuard
{
public:
    MutexLockGuard(MutexLock& mutex)
        :mutex_(mutex)
    {
        mutex_.lock();
    } 
    ~MutexLockGuard()
    {
        mutex_.unlock();
    }

private:
    MutexLock & mutex_;
};

#endif


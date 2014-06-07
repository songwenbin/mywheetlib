#ifndef _QUEUE_HEADER_
#define _QUEUE_HEADER_

#include "Condition.h"
#include "Mutex.h"

#include <deque>

template<typename T>
class Queue
{
public:
    Queue()
       :mutex_(),
        cond_(mutex_),
        queue_()
    {
    }

    void put(const T& x)
    {
        MutexLockGuard lock(mutex_);
        queue_.push_back(x);
        cond_.notify();
    }

    T take()
    {
        MutexLockGuard lock(mutex_); 
        while(queue_.empty())
        {
            cond_.wait();
        }

        T front(queue_.front());
        queue_.pop_front();

        return front;
    }

    size_t size()
    {
        MutexLockGuard lock(mutex_); 
        return queue_.size();
    }


private:
    MutexLock     mutex_;
    Condition     cond_;
    std::deque<T> queue_;
};

#endif

#ifndef _THREAD_POOL_HEADER_
#define _THREAD_POOL_HEADER_

#include <deque>
#include <vector>
#include <boost/function.hpp>

#include "Mutex.h"
#include "Condition.h"
#include "Thread.h"

class ThreadPool
{
public:
    typedef boost::function<void ()> Functor;
    ThreadPool(int maxSize);
    ~ThreadPool();

    void start(int numThreads);
    void stop();

    void put(const Functor & t);
    ThreadPool::Functor take();
    void worker(); 

private:
    std::vector<Thread *> threads_;
    std::deque<Functor>   queue_;     
    int maxSize_;
    int numThreads_;
    int running_;
    MutexLock mutex_;
    Condition notEmpty_;
    Condition notFull_;       
};

#endif

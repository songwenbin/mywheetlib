#include "ThreadPool.h"
#include <stdio.h>

ThreadPool::ThreadPool(int maxSize)
    : maxSize_(maxSize),
     notFull_(mutex_),
     notEmpty_(mutex_),
     running_(0)
{
}

ThreadPool::~ThreadPool()
{
    if(running_)
    {
       stop();
    }
}

void ThreadPool::start(int numThreads)
{
    numThreads_ = numThreads;
    running_ = 1;
    for(int i = 0; i < numThreads_; i++)
    {
        threads_.push_back(new Thread(boost::bind(&ThreadPool::worker, this)));
        threads_[i]->start();
    }
}

void ThreadPool::stop()
{
    {
       MutexLockGuard lock(mutex_);
       running_ = 0;
       notEmpty_.notifyAll();
    }

    for(int i = 0; i < numThreads_; i ++)
    {
        threads_[i]->join();
        delete threads_[i];
    }
}

void ThreadPool::worker()
{
    while(running_)
    {
       Functor func(take());
       if(func)
       {
           func();
       }
    }
}

void ThreadPool::put(const Functor & func)
{
    MutexLockGuard lock(mutex_);

    queue_.push_back(func);
    notEmpty_.notify();
}

ThreadPool::Functor ThreadPool::take()
{
    MutexLockGuard lock(mutex_);

    while(queue_.empty() && running_)
    {
        notEmpty_.wait();
    }

    Functor func;
    if(!queue_.empty())
    {
        func = queue_.front();
        queue_.pop_front();
    }

    return func; 
}
   

#ifndef _COUNT_LATCH_HEADER_
#define _COUNT_LATCH_HEADER_

class CountLatch
{
public:
    CountLatch(int count)
        :mutex_(),
         cond_(mutex_),
         count_(count)
    {
    }

    void wait()
    {
        MutexLockGuard lock(mutex_);
        while(count_ > 0)
        {
            cond_.wait();
        }
    }
         
    void countDown()
    {
        MutexLockGuard lock(mutex_);
        count_ --; 
        if(count_ == 0)
        {
            cond_.notifyAll();
        }
    }

    int getCount()
    {
        MutexLockGuard lock(mutex_);
        return count_;
    }

private:
    Condition cond_;
    MutexLock mutex_;
    int       count_;
};

#endif

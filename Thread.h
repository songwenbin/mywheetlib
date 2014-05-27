#ifndef _LU_THREAD_
#define _LU_THREAD_

#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <boost/noncopyable.hpp>

#include <pthread.h>

class Thread : boost::noncopyable
{
public:
    typedef boost::function<void ()> Function;
    
    Thread(const Function &);
    ~Thread();

    void start();
    void join();

private:
    pthread_t pid_;
    Function  func_;

};

#endif

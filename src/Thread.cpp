#include "Thread.h"

class ThreadData
{
public:
    typedef Thread::Function Function;
    ThreadData(const Function& func):func_(func) {};
    void run() { func_(); }
private:
    Function func_;
};

void * ThreadFunction(void * args)
{
    ThreadData * data = static_cast<ThreadData*>(args);
    data->run();
    delete data;
    return NULL;
}

Thread::Thread(const Function & func)
   :func_(func),
    pid_(0)
{
}

Thread::~Thread()
{

}

void Thread::start()
{
    ThreadData * data = new ThreadData(func_);
    if(pthread_create(&pid_, NULL, &ThreadFunction, data)) 
    {
    } 
}

void Thread::join()
{
    pthread_join(pid_, NULL);
}


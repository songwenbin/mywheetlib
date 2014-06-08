#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "Thread.h"
#include "ThreadPool.h"
#include "Queue.h"
#include "CountLatch.h"

class Test
{
public:
   void doit(int i) 
   { 
       printf("%d\n", i);
   }
};

int main()
{
    ThreadPool pool(16);

    Test t;
    for(int i = 0; i < 10; i ++)
    {
        pool.put(boost::bind(&Test::doit, t, i));
    }

    pool.start(3);
    sleep(1);

    printf("new data\n");
    pool.put(boost::bind(&Test::doit, t, 21));
    pool.put(boost::bind(&Test::doit, t, 22));
    sleep(1);

    return 0;
}

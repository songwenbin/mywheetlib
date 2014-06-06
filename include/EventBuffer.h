#ifndef _EVENT_BUFFER_HEADER_
#define _EVENT_BUFFER_HEADER_

#include <vector>
#include <stdio.h>
#include <sys/uio.h>

class EventBuffer
{
public:
    static const int BUFFERSIZE = 1024;
    EventBuffer() :buffer_(BUFFERSIZE)
    {
        initBuffer();
    }

    void initBuffer();

    // read data from fd to buffer
    ssize_t Read(int fd);

    // add data to buffer
    void append(const char * data, size_t len);

 
    // remove data from buffer
    void popData(size_t len);

    // get string in buffer
    char * getStr();

    // get the first address in buffer
    char * begin();

    // get the size of data buffer 
    size_t dataSize();

    // get the size of free buffer space 
    size_t freeSize();
     
private:
    std::vector<char> buffer_;
    int readDataIndex_;
    int freeMemIndex_;
};

#endif //_EVENT_BUFFER_HEADER_


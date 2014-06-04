#ifndef _EVENT_BUFFER_HEADER_
#define _EVENT_BUFFER_HEADER_

#include <vector>
#include <stdio.h>
#include <sys/uio.h>

class EventBuffer
{
public:
    static const int BUFFERSIZE = 1024;
    EventBuffer()
        :buffer_(BUFFERSIZE)
    {
        readDataIndex_ = 0;
        freeMemIndex_  = 0;
    }

    ssize_t Read(int fd)
    {
        char buffer[65536];

        struct iovec vec[2];
        vec[0].iov_base = begin() + freeMemIndex_; 
        vec[0].iov_len  = freeSize();
        vec[1].iov_base = buffer;
        vec[1].iov_len  = sizeof buffer;

        const ssize_t n = readv(fd, vec, 2);
        if(n < 0)
        {
            fprintf(stderr, "Reading buffer from fd is error!\n");
        }
        else if(n <= freeSize())
        {
            freeMemIndex_ += n;
        }
        else 
        {
            freeMemIndex_ = buffer_.size();
            append(buffer, n - freeSize());
        }

        return n;
    }

    void append(const char * data, size_t len)
    {
        resizeBuffer(len);        
        std::copy(data, data+len, begin() + freeMemIndex_);
    }
  
    void resizeBuffer(size_t len)  
    {
        assert(freeSize() >= len);
        buffer_.resize(freeMemIndex_ + len);
        freeMemIndex_ += len;
    }

    void retrieve(size_t len)
    {
         readDataIndex_ += len;
    }

    void retrieveAll()
    {
        readDataIndex_ = 0;
        freeMemIndex_  = 0;
    }
 
    char * peek()
    {
         return begin() + readDataIndex_;
    }

    char * begin()
    {
        return &*buffer_.begin(); 
    }

    size_t dataSize()
    {
        return freeMemIndex_ - readDataIndex_; 
    }

    size_t freeSize()
    {
        return buffer_.size() - freeMemIndex_;
    }
     
private:
    std::vector<char> buffer_;
    int readDataIndex_;
    int freeMemIndex_;
};

#endif //_BUFFER_HEADER_


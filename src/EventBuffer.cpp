#include "EventBuffer.h"


ssize_t EventBuffer::Read(int fd)
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

void EventBuffer::initBuffer()
{
    readDataIndex_ = 0;
    freeMemIndex_  = 0;
}

void EventBuffer::append(const char * data, size_t len)
{
    if(len >= freeSize())
    {
        //resize buffer
        buffer_.resize(freeMemIndex_ + len);
    }
    std::copy(data, data+len, begin() + freeMemIndex_);
    freeMemIndex_ += len;
}
 
void EventBuffer::popData(size_t len)
{
    if(readDataIndex_ + len <= buffer_.size())
    {
        readDataIndex_ += len;
    }
}

char * EventBuffer::getStr()
{
    return begin() + readDataIndex_;
}

char * EventBuffer::begin()
{
    return &*buffer_.begin(); 
}

size_t EventBuffer::dataSize()
{
    return freeMemIndex_ - readDataIndex_; 
}

size_t EventBuffer::freeSize()
{
    return buffer_.size() - freeMemIndex_;
}
     


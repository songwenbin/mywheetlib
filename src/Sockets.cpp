#include <Sockets.h>

uint64_t socketHost2Netwok64(uint64_t host64)
{
    return htobe64(host64);
}

uint64_t socketHost2Network32(uint32_t host32)
{
    return htobe32(host32);
}

uint16_t socketHost2Network16(uint16_t host16)
{
    return htobe16(host16);
}

uint64_t socketNetwork2Host64(uint64_t net64)
{
    return be64toh(net64);
}

uint32_t socketNetwork2Host32(uint32_t net32)
{
    return be32toh(net32);
}

uint16_t socketNetwork2Host16(uint16_t net16)
{
    return be16toh(net16);
}


void setNonBlock(int sockfd)
{
    int flags = fcntl(sockfd, F_GETFL, 0);
    flags |= O_NONBLOCK;
    int ret = fcntl(sockfd, F_SETFL, flags);

    flags = fcntl(sockfd, F_GETFD, 0);
    flags |= FD_CLOEXEC;
    ret = fcntl(sockfd, F_SETFD, flags);
}

int socketCreate()
{
    int sockfd = socket(AF_INET,
                        SOCK_STREAM | SOCK_NONBLOCK | SOCK_CLOEXEC,
                        IPPROTO_TCP);
    if(sockfd < 0)
    {
        fprintf(stderr, "failure in socketCreate\n");
    }
    return sockfd;
}

void socketBind(int sockfd, struct sockaddr_in & addr)
{
    int ret = bind(sockfd, (struct sockaddr *)(&addr), sizeof addr);
    if(ret < 0)
    {
        fprintf(stderr, "failure in socketBind\n");
    }
}

void socketListen(int sockfd)
{
    int ret = listen(sockfd, SOMAXCONN);
    if(ret < 0)
    {
        fprintf(stderr, "failure in socketListen");
    }
}

int socketAccept(int sockfd, struct sockaddr_in * addr)
{
    socklen_t addrlen = sizeof *addr;
    
    int connfd = accept(sockfd, (struct sockaddr *)addr, &addrlen);
    setNonBlock(connfd);

    if(connfd < 0)
    {
        int savedErrno = errno;
        switch(connfd)
        {
            case EAGAIN:
            case ECONNABORTED:
            case EINTR:
            case EPROTO:
            case EPERM:
            case EMFILE:
                errno = savedErrno;
                break;
            case EBADF:
            case EFAULT:
            case EINVAL:
            case ENFILE:
            case ENOBUFS:
            case ENOMEM:
            case ENOTSOCK:
            case EOPNOTSUPP:
                fprintf(stderr, "unexpected error : %d\n", savedErrno);
                break;
            default: 
                fprintf(stderr, "unkown error : %d\n", savedErrno);
                break;
        }
    }
    return connfd;
}

void socketClose(int sockfd)
{
     if(close(sockfd) < 0)
     {
         fprintf(stderr, "failure in socketClose\n");
     }
}

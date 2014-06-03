#ifndef _EVENT_SERVER_SOCKET_HEADER_
#define _EVENT_SERVER_SOCKET_HEADER_

#include "NetWorkAddress.h"
#include <boost/function.hpp>

class EventServerSocket
{
public:
     typedef boost::function<void (int, NetWorkAddress&)> CallBack;
    
     EventServerSocket(NetWorkAddress & listen);
     ~EventServerSocket();

     void handleRead();
     void listenConnection(); 
     
     int fd()
     {
         return acceptFd_;
     }

     void setActionAfterConn(const CallBack & cb)
     {
         actionAfterConnection_ = cb;
     }

private:
     CallBack actionAfterConnection_;
     int acceptFd_;
};

#endif

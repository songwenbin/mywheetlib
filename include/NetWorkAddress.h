#ifndef _NETWORK_ADDRESS_HEADER_
#define _NETWORK_ADDRESS_HEADER_

#include <netinet/in.h>
#include <string>
#include <string.h>
#include "Sockets.h"

class NetWorkAddress
{
public:
    NetWorkAddress(uint16_t port) 
    {
       bzero(&address_, sizeof address_);
       address_.sin_family = AF_INET;
       address_.sin_addr.s_addr = socketHost2Network32(INADDR_ANY);
       address_.sin_port = socketHost2Network16(port);
    }
    /*
    NetWorkAddress(std::string ip, uint16_t port)
    {
    }
    NetWorkAddress(struct sockaddr_in & address)
        :address_(address)
    {
    }
    */
    
    struct sockaddr_in & getSocketAddressInet()
    {
        return address_;
    }
private:
    struct sockaddr_in address_;
};

#endif

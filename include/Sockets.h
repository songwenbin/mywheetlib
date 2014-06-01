#ifndef _SOCKETS_HEADER_
#define _SOCKETS_HEADER_

#include <arpa/inet.h>
#include <endian.h>
#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <strings.h>
#include <stdint.h>
#include <endian.h>

uint64_t socketHost2Netwok64(uint64_t host64);

uint64_t socketHost2Network32(uint32_t host32);

uint16_t socketHost2Network16(uint16_t host16);

uint64_t socketNetwork2Host64(uint64_t net64);

uint32_t socketNetwork2Host32(uint32_t net32);

uint16_t socketNetwork2Host16(uint16_t net16);

void setNonBlock(int sockfd);

int socketCreate();

void socketBind(int sockfd, struct sockaddr_in & addr);

void socketListen(int sockfd);

int socketAccept(int sockfd, struct sockaddr_in * addr);

void socketClose(int sockfd);

#endif

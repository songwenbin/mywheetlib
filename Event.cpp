#include "Event.h"
#include <sys/epoll.h>

const int Event::NoneEvent  = 0;
const int Event::ReadEvent  = EPOLLIN | EPOLLPRI;
const int Event::WriteEvent = EPOLLOUT;

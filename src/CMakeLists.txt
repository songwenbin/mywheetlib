SET(src
    Event.cpp
    EventWait.cpp
    EventManager.cpp
    EventTimer.cpp
    EventNotifier.cpp
    Thread.cpp
    Sockets.cpp
    EventServerSocket.cpp
    EventTcpServer.cpp
    TcpConnection.cpp
    EventBuffer.cpp
    )

INCLUDE_DIRECTORIES(../include)

ADD_LIBRARY(talkthread ${src})

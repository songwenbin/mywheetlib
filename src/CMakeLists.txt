SET(src
    Event.cpp
    EventWait.cpp
    EventManager.cpp
    EventTimer.cpp
    EventNotifier.cpp
    Thread.cpp
    )

INCLUDE_DIRECTORIES(../include)

ADD_LIBRARY(talkthread ${src})

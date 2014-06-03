CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

PROJECT(TALKTHREAD)

FIND_PACKAGE(Boost REQUIRED)

ADD_SUBDIRECTORY(src)

INCLUDE_DIRECTORIES(include)

#ADD_EXECUTABLE(test Main.cpp)
#TARGET_LINK_LIBRARIES(test talkthread pthread)

ADD_EXECUTABLE(TestServerSocket TestServerSocket.cpp)
TARGET_LINK_LIBRARIES(TestServerSocket talkthread pthread)

ADD_EXECUTABLE(TestTcpServer TestTcpServer.cpp)
TARGET_LINK_LIBRARIES(TestTcpServer talkthread pthread)

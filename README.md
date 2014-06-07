talkthread
==========

### 简介

TalkThread是用于线程消息通讯的组件库  
用于方便的建立工作线程之间的消息传递，类似于Golang和Erlang的消息通讯模型
   
### Finish

1. 参考Muduo库的模式，实现了Reactor模式框架

### ToDo

1. 单元测试case  
2. 代码注释
3. 实际使用例子
4. 错误处理
5. 日志，线程等基本库

###编译

> $ mkdir build  
> $ cd build  
> $ cmake ..  
> $ make  

###运行

> $ ./TestTcpServer

可以用telnet 本机的5258端口进行测试

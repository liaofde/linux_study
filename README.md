# linux_study

# Linux-C-Programming
  
  [Linux 常用C函数（中文版)](http://net.pku.edu.cn/~yhf/linux_c/)  
  [https://github.com/niushiqi/Linux-study](https://github.com/niushiqi/Linux-study)  
  [[Linux系统] 编写一个守护进程](https://www.cnblogs.com/leokale-zz/p/12163493.html)  
  [apue](https://github.com/MeiK2333/apue)  

# linux进程间通信
## 管道( pipe )
管道是一种半双工的通信方式，数据只能单向流动，而且只能在具有亲缘关系的进程间使用。进程的亲缘关系通常是指父子进程关系。
## 有名管道 (named pipe) 
有名管道也是半双工的通信方式，但是它允许无亲缘关系进程间的通信。
## 信号量( semophore ) 
信号量是一个计数器，可以用来控制多个进程对共享资源的访问。它常作为一种锁机制，防止某进程正在访问共享资源时，其他进程也访问该资源。因此，主要作为进程间以及同一进程内不同线程之间的同步手段。
## 消息队列( message queue ) 
消息队列是由消息的链表，存放在内核中并由消息队列标识符标识。消息队列克服了信号传递信息少、管道只能承载无格式字节流以及缓冲区大小受限等缺点。
## 信号 ( sinal ) ： 信号是一种比较复杂的通信方式，用于通知接收进程某个事件已经发生。
## 共享内存( shared memory ) 
共享内存就是映射一段能被其他进程所访问的内存，这段共享内存由一个进程创建，但多个进程都可以访问。共享内存是最快的 IPC 方式，它是针对其他进程间通信方式运行效率低而专门设计的。它往往与其他通信机制，如信号两，配合使用，来实现进程间的同步和通信。
## 套接字( socket ) 
套解口也是一种进程间通信机制，与其他通信机制不同的是，它可用于不同及其间的进程通信。  
[https://www.cnblogs.com/mydomain/archive/2010/09/23/1833369.html](https://www.cnblogs.com/zgq0/p/8780893.html)  
[进程间通信-socket](https://www.cnblogs.com/thinkinglife/p/4518353.html)  


# linux串口通信
[Linux下串口編程遇到的接收数据错误及原因（0x0d,0x11接收错误）](https://www.cnblogs.com/zgq0/p/8078505.html)  

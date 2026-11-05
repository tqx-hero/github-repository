### Linux系统编程-库函数与系统调用

- #### 注册主程序的终止处理函数：

  ```c
  #include <stdlib.h>
  /**
  	注册function，该函数在进程进入退出流程时(调用exit(3)或main函数return时)，通过exit(3)调用。
  	可注册多个函数，一个函数也可以注册多次，exit(3)都会统统调用，而且调用顺序与注册顺序相反。
  	注册终止处理程序的函数最多个数受 ATEXIT_MAX 影响，具体可使用sysconf(_SC_ATEXIT_MAX)查看（APUE 2.5章节）。
  	return：
  		成功：返回0
  		失败：返回非0.
  */
  int atexit(void (*function)(void));
  ```

  > 注意：
  >
  > 1、库函数 `exit(3)` 在进程退出时会先调用终止处理程序，也就是 `atexit(3)`注册的函数，再关闭进程未关闭的文件流，最后再调用系统调用函数: `_exit(2)` 或`_Exit(2)`退出。这是注册终止处理程序可行的前提。
  >
  > 2、所以如果进程退出时使用的是`_exit(2)`与`_Exit(2)`这两个系统调用函数，进程会直接退出，不会调用注册的函数。
  >
  > 3、至于信号引起的程序终止，需要具体查看信号处理以及后续过程，具体以是否调用`exit(3)`为准。比如：没有自定义注册`SIGINT`信号处理函数，当内核给进程发送该信号，执行完成中断处理流程后，调用的是内核态的`do_exit()`,而不是标准库函数`exit(3)`，此时`atexit(3)`无效；但如果自定义了该信号处理，后面自行调用`exit(3)`退出，`atexit(3)`有效。

  ##### demo:

  ```c
  #include <stdio.h>
  #include <stdlib.h>
  #include <unistd.h>
  static void e1(){
          fprintf(stdout,"进程[%d] 调用函数e1()\n",getpid());
  }
  
  static void e2(){
          fprintf(stdout,"进程[%d] 调用函数e2()\n",getpid());
  }
  
  int main(){
  
          if(atexit(e1))
                  fprintf(stderr,"register e1() error\n");
          if(atexit(e1))
                  fprintf(stderr,"register e1() error\n");
          if(atexit(e2))
                  fprintf(stderr,"register e2() error\n");
          fprintf(stdout,"主进程[%d]结束\n",getpid());
      
      	//1、调用exit(0)/return 0，执行顺序是：main()-> e2() -> e1() -> e1(),并且是同一个进程
      	//exit(0);
      	//return 0;
      
          //2、调用_exit(2)与_Exit(2)，不会执行e1()与e2()
          //_exit(0);
      
      	//3、死循环中按下CTRL+C，产生SIGINT信号，不会执行后面的exit(0)，e1()与e2()不会执行
          //while(1);
          //exit(0);
  }
  ```

  

- 
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

  

- #### 函数之间的无条件跳转`setjmp(3)` / `longjmp(3)` :

  ```c
  #include <setjmp.h>
  /**
  	将调用时的运行环境信息（通常包括栈指针、指令指针，还可能包含其他寄存器值、信号掩码）保存到缓冲区 `env`，供后续 `longjmp()` 使用。
  	第一次调用 `setjmp()` 时，返回值是 `0`。
  	env： 要保存现场的缓冲区，建议设定为全局变量，这样多个函数之间可共用
  	return：
  		成功：第一次调用该函数时，返回值固定是0.
  			后续返回值根据longjmp(3)的第二个参数val决定：
  				val = 0 ： 返回1
  				val ！=0： 返回val
  		可以通过返回值来辨别从哪个函数跳转过来的
  */
  int setjmp(jmp_buf env);
  /**
  	可以设定是否保存进程的信号掩码。除此之外功能与setjmp(3)相同。
  	env：存放现场数据的缓冲区
  	savesigs：是否将进程的信号掩码保存到缓冲区
  		0：不保存，功能等价于setjmp(3)
  		非0：保存信号掩码。当使用siglongjmp(3)返回时，进程的信号掩码也会恢复到之前。
  */
  int sigsetjmp(sigjmp_buf env, int savesigs);
  
  /**
  	栈帧之间的跳转，并设定val，setjmp(3)那边作为返回值处理。
  	使用保存在 `env` 中的信息，将控制流切回到当初调用 `setjmp()` 的位置，并把栈 “回卷” 到 `setjmp()` 那一刻的状态。
  	env： setjmp(3)存放的栈的现场的缓冲区。
  	val：要传到setjmp(3)的值。
  */
  void longjmp(jmp_buf env, int val);
  //返回到sigsetjmp(3)位置，与这个函数绑定使用
  void siglongjmp(sigjmp_buf env, int val);
  ```

  > 1、如果要保存进程的信号掩码，不要使用 `setjmp(3)`，必须使用 `sigsetjmp(3)`。
  > 2、`setjmp(3)` 的功能是保存栈的状态到缓冲区，当调用 `longjmp(3)` 时，会把缓冲区中的栈信息覆盖到当前栈，调用之前的栈帧都会消失。
  >
  > 3、保存现场的数据：
  >
  > ​	已确定的是栈指针、`EIP`寄存器(也就是PC寄存器)、进程的信号掩码(使用 `sigsetjmp(3)` 时)；
  >
  > 4、不会保存的数据：
  >
  > ​	全局变量、静态区变量不会恢复(因为只会保存栈与PC相关信息)。
  >
  > 5、至于自动变量(`auto`显式或隐式声明的局部变量)，不同的系统可能会有不同的行为，如果要明确不回滚，可以使用`volatile`修饰。

  ###### demo:函数间的跳转示例

  ```c
  #include <stdio.h>
  #include <stdlib.h>
  #include <setjmp.h>
  //使用setjmp(3)、longjump(3)实现非局部跳转，也就是栈帧之间跳转
  jmp_buf jb;
  int cnt;	//分别定义静态变量、全局变量
  static int num;
  void f1(){
          fprintf(stdout,"f1() ...\n");
          longjmp(jb,1);
  }
  
  void f2(){
          fprintf(stdout,"f2() ...\n");
          longjmp(jb,2);
  }
  
  int main(){
          int ret;
          volatile int autonum = 100; //定义不让编译器优化的自动局部变量
          cnt += 20;
          num = 30;
          if(!(ret = setjmp(jb))){
                  //刚执行setjmp(3)保存现场,longjmp(3)还未被调用,返回值等于0
                  fprintf(stdout,"into the func...\n");
                  cnt += 1;
                  num += 1;
                  autonum += 1000;
                  f1();
          }else if(ret == 1){//从longjmp(3)设置值1那里跳转过来
                  fprintf(stdout,"从1那里跳转过来的...\n");
                  f2();
          }else {
                  fprintf(stdout,"从2那里跳转过来的..\n");
          }
          fprintf(stdout,"正在退出...\n");
          fprintf(stdout,"cnt = %d,num = %d,autonum = %d\n",cnt,num,autonum);
          exit(0);
  }
  ```

  输出结果：

  ```bash
  $ ./longjump
  
  into the func...	#第一次执行setjmp(3)
  f1() ...			#执行f1()
  从1那里跳转过来的...	#从f1()跳转到了main()函数的setjmp(3)位置，并且走ret == 1分支
  f2() ...			#进入f2()
  从2那里跳转过来的..		#从f2()跳转回来，走 ret == 2分支
  正在退出...
  cnt = 21,num = 31,autonum = 1100	#这三种变量恢复现场后不会回滚。
  ```

  

- 
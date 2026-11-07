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

  

- #### 获取资源限制值：

  - **软限制（`rlim_cur，soft limit`）**：日常生效的警告 / 触发阈值，进程**自己可以把它调高，但最高不能超过硬限制**；超限会触发信号 / 失败。
  - **硬限制（`rlim_max，hard limit`）**：这是该资源的天花板，是软限制能到达的上限；**普通进程不能调高硬限制，只能降低硬限制，但是降低后就无法太高了，只有特权进程（`root/CAP_SYS_RESOURCE`）才可以抬高硬限制**。

  ```c
  #include <sys/resource.h>
  /**
  	根据资源类型获取进程所拥有的该资源当前值与最大值限制。
  	resource：资源类型，具体见下方表格
  	rlp：存放限制值的结构体地址，getrlimit(3)则会对结果回填，setrlimit(3)则会将该地址数据设置到环境。
  	return：
  		成功：0
  		失败：-1，填充errno
  */
  int getrlimit(int resource, struct rlimit *rlp);
  int setrlimit(int resource, const struct rlimit *rlp);
  
  typedef unsigned long rlim_t;
  struct rlimit {
      rlim_t rlim_cur;	//当前限制，也叫软限制
      rlim_t rlim_max;	//软限制的最大限度值，也叫硬限制(硬限制必须要不小于软限制)
  }
  ```

  资源类型：

  | 宏名            | 含义                                             | 单位 | 超限行为                                                     |
  | --------------- | ------------------------------------------------ | ---- | ------------------------------------------------------------ |
  | `RLIMIT_CORE`   | 进程可生成的 core 文件最大尺寸                   | 字节 | 限制值为 0：禁止生成 core 文件；超出上限时，core 文件写到该大小就停止 |
  | `RLIMIT_CPU`    | 进程最多可占用的 CPU 时长                        | 秒   | 超出上限发送 `SIGXCPU`；若进程捕获 / 忽略该信号，或该进程所有线程阻塞该信号，行为未定义 |
  | `RLIMIT_DATA`   | 进程数据段最大尺寸(`data+bss+heap`)              | 字节 | 超出时 `malloc()` 失败，`errno = ENOMEM`                     |
  | `RLIMIT_FSIZE`  | 进程可创建的单个文件最大尺寸                     | 字节 | write /truncate 将超限时，向线程发送 `SIGXFSZ`；线程阻塞该信号、或进程捕获 / 忽略该信号时，继续扩文件会失败，`errno = EFBIG` |
  | `RLIMIT_NOFILE` | 新分配文件描述符的上限（实际最大 fd = 该值 − 1） | 计数 | 超出时分配 fd 的函数失败，`errno = EMFILE`；限制一个进程持有的文件描述符总数 |
  | `RLIMIT_STACK`  | 初始线程栈的最大尺寸                             | 字节 | 实现不会自动把栈增长超过该限制；超限发送 `SIGSEGV`；若线程阻塞该信号，或进程捕获 / 忽略且未配置备用栈，发送信号前会将处置重置为 `SIG_DFL` |
  | `RLIMIT_AS`     | 进程整个地址空间可用内存上限                     | 字节 | 超出时 `malloc()`、`mmap()` 失败，`errno = ENOMEM`；同时栈的自动增长也会失效，并触发上面栈超限相关效果 |

  ***对于返回值，有以下情况：***

  ***1、如果返回值还没有限制，返回 `RLIM_INFINITY` .***

  ***2、如果返回值过大，以至于超过了软硬限制，返回 `RLIM_SAVED_MAX` 或 `RLIM_SAVED_CUR`***

  ***3、除以上情况，值正常返回。***

  ###### 对于设置值时：

  > 调用 `setrlimit()` 时：

  - 如果请求的新限制值是 `RLIM_INFINITY`：新限制设为「无限制」；
  - 否则，如果请求值是 `RLIM_SAVED_MAX`：新限制取对应的**已保存硬限制**；
  - 否则，如果请求值是 `RLIM_SAVED_CUR`：新限制取对应的**已保存软限制**；
  - 其余情况：直接使用传入的这个数值作为新限制。

  另外：如果对应的那条已保存限制可以无损存入 `rlim_t`，则该保存值会被这个新限制覆盖。

  > 除非之前某次 `getrlimit()` 在该资源上恰好返回过 `RLIM_SAVED_MAX` / `RLIM_SAVED_CUR`，否则你直接把限制设为这两个宏之一时，行为是未定义的。

  

  ###### demo：获取Linux系统下的限制值：

  ```c
  #include <stdio.h>
  #include <stdlib.h>
  #include <sys/resource.h>
  #include <setjmp.h>
  //getrlimit(3)函数的使用
  
  //使用了宏替换，将宏名与宏值一并带过去
  #define do_get(name) print_limit(#name,name)
  
  sigjmp_buf jb;
  
  void print_limit(char *name,int value);
  
  int main(){
          if(!sigsetjmp(jb,1)){
                  do_get(RLIMIT_AS);
                  do_get(RLIMIT_CORE);
                  do_get(RLIMIT_CPU);
                  do_get(RLIMIT_DATA);
                  do_get(RLIMIT_FSIZE);
                  do_get(RLIMIT_NOFILE);
                  do_get(RLIMIT_STACK);
  #ifdef  RLIMIT_MSGQUEUE
                  do_get(RLIMIT_MSGQUEUE);
  #endif
  
  #ifdef  RLIMIT_NICE
                  do_get(RLIMIT_NICE);
  #endif
  
  #ifdef  RLIMIT_NPROC
                  do_get(RLIMIT_NPROC);
  #endif
  
  #ifdef  RLIMIT_RSS
                  do_get(RLIMIT_RSS);
  #endif
  
  #ifdef  RLIMIT_SIGPENDING
                  do_get(RLIMIT_SIGPENDING);
  #endif
  
  #ifdef  RLIMIT_SWAP
                  do_get(RLIMIT_SWAP);
  #endif
          }else
                  fprintf(stderr,"getrlimit fail.\n");
          return 0;
  }
  
  void print_limit(char *name,int value){
          struct rlimit limit;
          if(getrlimit(value,&limit) < 0){
                  perror("getrlimit() error");
                  siglongjmp(jb,1);
          }
          fprintf(stdout,"%s  ",name);
          if(limit.rlim_cur == RLIM_INFINITY)
                  fprintf(stdout,"(unlimited)  ");
          else if(limit.rlim_cur == RLIM_SAVED_CUR)
                  fprintf(stdout,"(too big)  ");
          else
                  fprintf(stdout,"%lu  ",limit.rlim_cur);
  
          if(limit.rlim_max == RLIM_INFINITY)
                  fprintf(stdout,"(unlimited)  ");
          else if(limit.rlim_max == RLIM_SAVED_MAX)
                  fprintf(stdout,"(too big)  ");
          else
                  fprintf(stdout,"%lu  ",limit.rlim_max);
          fprintf(stdout,"\n");
          return;
  }
  ```

  输出结果：

  ```bash
  $ ./getrlimit
  
  RLIMIT_AS  (unlimited)  (unlimited)
  RLIMIT_CORE  0  (unlimited)
  RLIMIT_CPU  (unlimited)  (unlimited)
  RLIMIT_DATA  (unlimited)  (unlimited)
  RLIMIT_FSIZE  (unlimited)  (unlimited)
  RLIMIT_NOFILE  1024  1048576
  RLIMIT_STACK  8388608  (unlimited)
  RLIMIT_MSGQUEUE  819200  819200
  RLIMIT_NICE  0  0
  RLIMIT_NPROC  15115  15115
  RLIMIT_RSS  (unlimited)  (unlimited)
  RLIMIT_SIGPENDING  15115  15115
  ```

  ###### demo:设置栈大小,软限制为1M，硬限制为8M

  ```c
  #include <stdio.h>
  #include <stdlib.h>
  #include <sys/resource.h>
  //setrlimit(3)函数的使用
  int main(){
          //这里直接设置栈大小
          struct rlimit limit,r_limit;
          limit.rlim_cur = 1024 * 1024;
          //limit.rlim_max = RLIM_INFINITY;
          limit.rlim_max = 8 * 1024 * 1024;
          if(setrlimit(RLIMIT_STACK,&limit) < 0)
                  perror("setrlimit() error");
          //读取栈大小限制
          if(getrlimit(RLIMIT_STACK,&r_limit) < 0)
                  perror("getrlimit() error");
          //fprintf(stdout,"cur = %lu,max == unlimit ? %d\n",r_limit.rlim_cur,r_limit.rlim_max == RLIM_INFINITY);
          fprintf(stdout,"cur = %lu,max == %lu\n",r_limit.rlim_cur,r_limit.rlim_max);
          return 0;
  }

- #### 加密函数crypt(3):

  ```c
  #define _XOPEN_SOURCE       /* See feature_test_macros(7) */
  #include <unistd.h>
  /**
  	给输入口令按照某个salt进行加密。返回密文。
  	key：真实口令
  	salt：是从集合 `[a–zA–Z0–9./]` 中选出的一个两字符字符串。该串用于把算法扰动为 4096 种不同变体之一。
  	关于salt的构成参考下面的描述。
  	return:
  		成功：加密后的字符串
  		失败：NULL，填充errno
  */
  char *crypt(const char *key, const char *salt);
  
  #define _GNU_SOURCE         /* See feature_test_macros(7) */
  #include <crypt.h>
  
  char *crypt_r(const char *key, const char *salt,
               struct crypt_data *data);
  
  Link with -lcrypt.
  ```

  ###### salt：

  glibc2 版本的该函数额外支持多种哈希算法。
  如果传入的 salt 是以 `$id$` 开头、并以 `$` 收尾的字符串：

  ```
  $id$salt$encrypted
  ```

  则不会使用老式 DES 流程；`id` 用来指定采用哪一种算法，同时决定后续串如何解析。支持的 id：

  表格

  | ID   | 算法                                                      |
  | ---- | --------------------------------------------------------- |
  | 1    | MD5                                                       |
  | 2a   | Blowfish（主线 glibc 原生不支持，仅部分发行版打补丁加入） |
  | 5    | SHA‑256（glibc 2.7 起）                                   |
  | 6    | SHA‑512（glibc 2.7 起）                                   |

  因此 `$5$salt$encrypted` 代表 SHA‑256 口令哈希，`$6$salt$encrypted` 代表 SHA‑512。

  这里的 salt，指 `$id$` 之后最多 16 个字符。`encrypted` 段才是最终算出的哈希摘要。这一段长度固定：

  - MD5：22 字符
  - SHA‑256：43 字符
  - SHA‑512：86 字符

  salt 和 encrypted 部分的字符都取自集合 `[a–zA–Z0–9./]`。在 `MD5`、`SHA` 这几套实现里，**整个口令都会参与计算**，不再像老 DES crypt 那样只取前 8 字节。

- #### 暂时关闭终端回显功能，以指定方式显示内容：

  ```c
  #include <unistd.h>
  /**
  	显示prompt内容的提示，阻塞等待终端输入内容，不显示键入内容，返回键入的内容。相较于gets(3)，多了提示字符串，少了显示输入的内容，适用于口令输入。
  	(该函数已被废弃，多线程不安全，可使用termios(3)的ECHO选项设置)
  */
  char *getpass( const char *prompt);
  ```

  ##### demo：实现用户登录密码校验：

  ```c
  #include <stdio.h>
  #include <stdlib.h>
  #include <unistd.h>
  #include <string.h>
  #include <shadow.h>
  #include <termios.h>
  
  //加密算法
  
  struct spwd* Getspnam(const char* name){
          struct spwd * spw;
          if(!(spw = getspnam(name))){
                  perror("getspnam() error");
                  exit(1);
          }
          return spw;
  }
  
  char * Getpass(const char*prompt){
          char * pwd;
          if(!(pwd = getpass(prompt))){
                  perror("getpass() error");
                  exit(1);
          }
          return pwd;
  }
  
  char* Crypt(const char* pwd,const char* salt){
          char * ret;
          if(!(ret = crypt(pwd,salt))){
                  perror("crypt() error");
                  exit(1);
          }
          return ret;
  }
  
  int main(int argc,char **argv){
          char *encode,*getpass_info;
          struct spwd *shadow_info;
          struct termios old,news;
          char pwd[512];
          if(argc < 2){
                  fprintf(stderr,"需要传入用户名\n");
                  exit(1);
          }
          //需要键入密码,下面是2种方法：
          //1、使用getpass(3)获取的字符串，就是后面的pwd
          //getpass_info = Getpass("Please enter your passwd: ");
  
          //2、使用termios选项
          fprintf(stdout,"Please enter your passwd : ");
          fflush(stdout);
          tcgetattr(STDIN_FILENO,&old); //获取当前输入流的终端属性
          memcpy(&news,&old,sizeof(news));
          news.c_lflag &= ~ECHO; //设置关闭回显功能选项
          news.c_lflag &= ~ECHONL;
          tcsetattr(STDIN_FILENO,TCSAFLUSH,&news); //关闭回显功能
  	    //获取阴影口令上下文
          fgets(pwd,sizeof(pwd),stdin);
          tcsetattr(STDIN_FILENO,TCSAFLUSH,&old);   //恢复现场 
          pwd[strlen(pwd) - 1] = 0;	//去掉输入的 \n
          fprintf(stdout,"\n");
          shadow_info = Getspnam(argv[1]); //通过参数用户名获取阴影口令文件的内容
          encode = Crypt(pwd,shadow_info->sp_pwdp); //加密，使用键入的口令 + 阴影口令，函数对阴影口令会自动截取前3个$的有效子串进行加密
          fprintf(stdout,"encode = %s\n",encode);
          fprintf(stdout,"shadow_encode = %s\n",shadow_info->sp_pwdp);
          fprintf(stdout,"match ? %d\n",strcmp(encode,shadow_info->sp_pwdp) == 0); //比较是否匹配
          return 0;
  }
  ```

  ###### 输出结果：注意获取阴影口令函数是需要root权限的。

  ```bash
   ./crypt tqx
   
  Please enter your passwd :	#关闭了回显功能，内容就不会显示
  密码是：tqx	#恢复回显功能后的输出
  encode = $6$tND/cQczrwpCPBb8$d0jB1/0CM9K86DMeDy/dNff8MDDHVImDqJ80bVXtT7hj5mxQ/5F1bzUArQGLpNYvyrhB8Sp9TvunTBeqRZUik/
  shadow_encode = $6$tND/cQczrwpCPBb8$d0jB1/0CM9K86DMeDy/dNff8MDDHVImDqJ80bVXtT7hj5mxQ/5F1bzUArQGLpNYvyrhB8Sp9TvunTBeqRZUik/
  match ? 1
  ```

  

- 
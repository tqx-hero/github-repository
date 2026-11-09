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

  

- #### 解析命令行参数，获取相关形式的时间：

  ```c
  #include <stdio.h>
  #include <stdlib.h>
  #include <unistd.h>
  #include <string.h>
  #include <time.h>
  #define FMT_BUFSIZ 512
  #define TIME_BUF_SIZ 512
  #define         SWITCH_OPT(num,str)     case num :                                       \
                                                  strncat(fmtbuf,str,remain_size);                         \
                                                  remain_size = FMT_BUFSIZ - strlen(fmtbuf);\
                                          break
  //使用命令行参数解析函数getopt(3)
  //以解析当前时间为例，根据不同的选项输入，返回选项所代表的时间值
  /**
   *      Y：年
   *      m：月
   *      d：日
   *      H：小时
   *      M：分钟
   *      S：秒
   */
  int main(int argc,char ** argv){
          //1、getopt(3)函数解析命令选项，生成fmt字符出
          int optval;
          char fmtbuf[FMT_BUFSIZ],time_buf[TIME_BUF_SIZ];
          size_t remain_size;
          time_t ctime;
          struct tm *tmp;
          remain_size = FMT_BUFSIZ;
      	//getopt(3)解析短命令，拼接格式化字符串
          while((optval = getopt(argc,argv,"YmdHMS")) > 0){
                  switch(optval){
                          SWITCH_OPT('Y',"%Y ");
                          SWITCH_OPT('m',"%m ");
                          SWITCH_OPT('d',"%d ");
                          SWITCH_OPT('H',"%H ");
                          SWITCH_OPT('M',"%M ");
                          SWITCH_OPT('S',"%S ");
                          default:
                                  break;
                  }
          }
  
          //2、根据fmt使用strftime(3)解析当前的时间，输出
          ctime = time(NULL);
          tmp = localtime(&ctime);
          strftime(time_buf,sizeof(time_buf),fmtbuf,tmp);
          puts(time_buf);
          exit(0);
  }
  ```

  

- #### 实现指令：`ls`功能，目前支持的选项有：`-a -l -i -n`

  ```c
  #include <stdio.h>
  #include <stdlib.h>
  #include <sys/stat.h>
  #include <unistd.h>
  #include <fcntl.h>
  #include <string.h>
  #include <sys/types.h>
  #include <pwd.h>
  #include <grp.h>
  #include <glob.h>
  #include <time.h>
  /***********要查询的文件名最大数量****************/
  #define REQUEST_PATH_SIZE 128
  
  /***********权限与时间字符串缓冲区的最小大小****************/
  #define MODE_BUF_SZ_MIN 16
  #define TIME_BUF_SZ_MIN 128
  
  /***********权限与时间字符串缓冲区的当前大小****************/
  #define MODE_BUF_SIZ 16
  #define TIME_BUF_SIZ 128
  
  /*********定义展示哪些字段的宏***************/
  
  //展示INODE号码
  #define SHOW_INODE 001
  //展示所有文件，包括隐藏文件
  #define SHOW_ALL 002
  //以列表形式展示，展示用户名与组名
  #define SHOW_LIST 004
  //列表展示，展示用户ID+GID
  #define SHOW_IDS 010
  
  typedef unsigned long int show_flg_t;//选项的类型
  
  //宏函数，用于清空标志位
  #define show_flag_clear(flg_name) flg_name = 0L
  
  //switch() 中的case语句
  #define MODE_CASE(type,val)     case type :             \
                                          ret = val;      \
                                  break
  
  //实现ls功能，附加选项有-a -l -n -i
  // -i :显示inode号码.
  // -a:显示所有文件名，包括隐藏文件
  // -l:列表形式显示，显示文件所属+组名
  // -n：列表形式显示，显示文件属主ID+组ID
  
  //解析命令行参数
  void parse_arguments(int argc,char * const * argv,const char *optstr,\
                                    char **filepath,int *filepath_sizep,show_flg_t *show_flags);
  //格式化时间，放入缓冲区
  void format_time(char *time_buf,size_t bufsize,time_t t);
  //格式化权限字符串，放入缓冲区
  void config_mode(char *mode_buf,size_t modesize,mode_t mode);
  //打印文件相关的内容
  void print_file(int flags,struct stat *st,const char *filepath);
  
  /***********包裹函数***************/
  int Lstat(const char *path, struct stat *buf);
  struct passwd *Getpwuid(uid_t uid);
  struct group *Getgrgid(gid_t gid);
  int Chdir(const char *path);
  char *Getcwd(char *buf,size_t sz);
  int Glob(const char *pattern, int flags,
                                  int (*errfunc) (const char *epath, int eerrno),
                                                  glob_t *pglob);
  
  //实现自定义的功能myls ，可使用的选项：-l -n -i -a
  int main(int argc,char **argv){
          int i;
          char *filepath[REQUEST_PATH_SIZE];//解析命令行得到的文件名数组
          int filepath_size; //文件名个数
          show_flg_t flags;	//选项位图
          static struct stat st;
          glob_t glb;
          size_t j;
          char *lineptr;//字符 / 在路径中最后出现的偏移量，作用于截取文件名
          char *current_dirp; //记录当前目录
          if(TIME_BUF_SIZ < TIME_BUF_SZ_MIN){
                  fprintf(stderr,"Invalid sizeof(time_buf)! \n");
                  exit(1);
          }
  
          if(MODE_BUF_SIZ < MODE_BUF_SZ_MIN){
                  fprintf(stderr,"Invalid sizeof(mode_buf)! \n");
                  exit(1);
          }
      
          //记录当前工作目录
          current_dirp = Getcwd(NULL,0);
  		
      	//清空选项标志位，解析命令行参数
          show_flag_clear(flags);
          parse_arguments(argc,argv,"-lina",filepath,&filepath_size,&flags);
  
          //开始遍历文件路径的数组，逐个调用lstat(2)函数，获取它们的属性
          for(i = 0;i < filepath_size;++i){
                  Lstat(filepath[i],&st);
  
                  fprintf(stdout,"%s: \n",filepath[i]);
  
                  //如果是目录，打开目录获取下方值
                  if(S_ISDIR(st.st_mode)){
                          //改变工作目录到这个文件夹
                          Chdir(filepath[i]);
                      	//使用glob(3)获取该文件夹下的所有非文件
                          Glob("*",0,NULL,&glb);
                      
                          //如果需要展示所有文件，那就追加隐藏文件
                          if(flags & SHOW_ALL)
                                  Glob(".*",GLOB_APPEND,NULL,&glb);
                      
                          //遍历所有文件名，获取它们的属性
                          for(j = 0;j < glb.gl_pathc;++j){
                                  Lstat(glb.gl_pathv[j],&st);
                                  print_file(flags,&st,glb.gl_pathv[j]);
                          }
                      
                          globfree(&glb);
  
                          //恢复工作目录
                          Chdir(current_dirp);
                  }
                  else{
                          //如果是文件，直接调用下方
                          //按照 /截取文件名用于输出
                          lineptr = strrchr(filepath[i],'/');
                          if(lineptr) //存在 /,展示后面的文件名
                                  print_file(flags,&st,lineptr + 1);
                          else	//不存在 /,展示这个文件名
                                  print_file(flags,&st,filepath[i]);
                  }
                  fprintf(stdout,"\n");
          }
          fprintf(stdout,"\n");
          exit(0);
  }
  
  int Chdir(const char *path){
          int ret;
          if((ret = chdir(path)) < 0){
                  perror("chdir() error");
                  exit(1);
          }
          return ret;
  }
  
  char *Getcwd(char *buf,size_t sz){
          char *ptr;
          if(!(ptr = getcwd(buf,sz))){
                  perror("getcwd() error");
                  exit(1);
          }
          return ptr;
  }
  
  int Glob(const char *pattern, int flags,
                                  int (*errfunc) (const char *epath, int eerrno),
                                          glob_t *pglob){
          int ret;
          if(ret = glob(pattern,flags,errfunc,pglob))
                  perror("glob() error");
          return ret;
  }
  
  void print_file(int flags,struct stat *st,const char *filepath){
          struct passwd *pwd;
          struct group *grp;
          char time_buf[TIME_BUF_SIZ];
          char mode_buf[MODE_BUF_SIZ];
          //拼接属性值
          //1、是否获取INODE
          if(flags & SHOW_INODE)
                  fprintf(stdout,"%8lu ",st->st_ino);
          if(flags & SHOW_LIST){
                  //2、拼接权限
                  memset(mode_buf,0,sizeof(mode_buf));
                  config_mode(mode_buf,sizeof(mode_buf),st->st_mode);
                  fprintf(stdout,"%s ",mode_buf);
  
                  //展示链接数
                  fprintf(stdout,"%2lu ",st->st_nlink);
  
                  //有n选项就显示用户ID与组ID，否则显示用户名与组名
                  if(flags & SHOW_IDS)
                          fprintf(stdout,"%4lu %4lu ",st->st_uid,st->st_gid);
                  else{  //显示用户名与组名
                          pwd = Getpwuid(st->st_uid);
                          grp = Getgrgid(st->st_gid);
                          fprintf(stdout,"%s %s ",pwd->pw_name,grp->gr_name);
                  }
  
                  //写入大小
                  fprintf(stdout,"%5lu ",st->st_size);
  
                  //写入时间：这里是最后一次修改时间，以 月份 日 时:分形式
                  format_time(time_buf,sizeof(time_buf),st->st_mtime);
                  fprintf(stdout,"%s ",time_buf);
                  //最后加入文件名，并添加换行
                  fprintf(stdout,"%s\n",filepath);
          }else
                  //最后加入文件名，并添加换行
                  fprintf(stdout,"%s ",filepath);
  }
  
  struct tm *Localtime(const time_t *timep){
          struct tm *tim;
          if((tim = localtime(timep)) == NULL){
                  perror("localtime() error");
                  exit(1);
          }
          return tim;
  }
  
  size_t Strftime(char *s, size_t max, const char *fmt,const struct tm *tm){
          size_t sz;
          if((sz = strftime(s,max,fmt,tm)) == 0){
                  perror("strftime() error");
                  exit(1);
          }
          return sz;
  }
  //辨别文件类型
  int config_file_type(mode_t mode){
          int ret;
          switch(mode & S_IFMT){
                  MODE_CASE(S_IFREG,'-');
                  MODE_CASE(S_IFDIR,'d');
                  MODE_CASE(S_IFCHR,'c');
                  MODE_CASE(S_IFBLK,'b');
                  MODE_CASE(S_IFIFO,'p');
                  MODE_CASE(S_IFSOCK,'s');
                  MODE_CASE(S_IFLNK,'l');
                  default :
                          fprintf(stderr,"参数出错，进程退出!\n");
                          _exit(1);
                  break;
          }
          return ret;
  }
  /**********************拼接权限字符串的宏************************************/
  #define MODE_PERMISSION(type,val1,val2,index)   if(mode & (type))       \
                                                   mode_buf[index] = val1;\
                                                  else                    \
                                                   mode_buf[index] = val2
  
  #define MODE_PERMISSION_SID(type1,type2,val1,val2,val3,index)  if((mode & (type1)) == 0)\
                                                          mode_buf[index] =  val3;        \
                                                     else if(mode & (type2))              \
                                                          mode_buf[index] = val2;         \
                                                     else                                 \
                                                          mode_buf[index] = val1
  
  void config_mode(char *mode_buf,size_t modesize,mode_t mode){
          mode_buf[0] = config_file_type(mode);
          //当前用户权限
          MODE_PERMISSION(S_IRUSR,'r','-',1);
          MODE_PERMISSION(S_IWUSR,'w','-',2);
          MODE_PERMISSION_SID(S_IXUSR,S_ISUID,'x','s','-',3);
  
          //组
          MODE_PERMISSION(S_IRGRP,'r','-',4);
          MODE_PERMISSION(S_IWGRP,'w','-',5);
          MODE_PERMISSION_SID(S_IXGRP,S_ISGID,'x','s','-',6);
  
          //其他
          MODE_PERMISSION(S_IROTH,'r','-',7);
          MODE_PERMISSION(S_IWOTH,'w','-',8);
          MODE_PERMISSION(S_IXOTH,'x','-',9);
  
          //粘着位
          MODE_PERMISSION(S_ISVTX,'t',mode_buf[9],9);
          mode_buf[10] = '.';
  }
  
  void format_time(char *time_buf,size_t bufsize,time_t t){
          struct tm *tmp;
          tmp = Localtime(&t);
          Strftime(time_buf,bufsize,"%b %e %H:%M",tmp);
  }
  
  struct group *Getgrgid(gid_t gid){
          struct group* grp;
          if(!(grp = getgrgid(gid))){
                  perror("getgrgid() error");
                  exit(1);
          }
          return grp;
  }
  
  struct passwd *Getpwuid(uid_t uid){
          struct passwd *pwd;
          if(!(pwd = getpwuid(uid))){
                  perror("getpwuid() error");
                  exit(1);
          }
          return pwd;
  }
  
  int Lstat(const char *path, struct stat *buf){
          int ret;
          if((ret = lstat(path,buf)) < 0){
                  perror("lstat() error");
                  exit(1);
          }
          return ret;
  }
  
  void parse_arguments(int argc,char * const * argv,const char *optstr,\
                  char **filepath,int *filepath_sizep,show_flg_t *show_flags){
          int size = 0;
          int optval;
          while((optval = getopt(argc,argv,optstr)) > 0){//getopt(3)解析选项，存在的将选项位置1
                  switch(optval){
                          case 'l':
                                  *show_flags |= SHOW_LIST;
                                  break;
                          case 'i':
                                  *show_flags |= SHOW_INODE;
                                  break;
                          case 'n':
                                  *show_flags |= SHOW_IDS | SHOW_LIST;
                                  break;
                          case 'a':
                                  *show_flags |= SHOW_ALL;
                                  break;
                          case 1 : //文件名，将其放入数组
                                  filepath[size++] = argv[optind - 1];
                                  break;
                          default :
                                  fprintf(stderr,"occur error..\n");
                                  _exit(1);
                                  break;
                  }
          }
          //如果没有声明查询的文件名，将当前目录写入
          if(!size)
                  filepath[size++] = ".";
          *filepath_sizep = size;
          return;
  }
  ```

  输出结果：

  ```bash
  $ ./a.out -lni  ..  .	#展示上级目录 & 当前目录的文件列表
  ..:
   1528772 drwxrwxrwx.  3 1000 1000   132 Nov  7 12:29 page3
  55591093 drwxrwxrwx.  3 1000 1000   268 Nov  9 21:32 page4
  55573487 drwxrwxrwx.  3 1000 1000   140 Nov  7 12:29 page5
  19018418 drwxrwxrwx.  2 1000 1000   226 Nov  8 17:48 page6
  35382892 drwxrwxrwx.  2 1000 1000   110 Nov  7 12:29 page7
  52505446 drwxrwxrwx.  2 1000 1000   134 Nov  7 12:29 practise
  
  .:
  55588412 -rw-rw-r--.  1 1000 1000    32 Nov  7 12:29 Makefile
  55591076 -rwxrwxr-x.  1 1000 1000 20176 Nov  9 21:32 a.out
  55591094 -rw-rw-r--.  1 1000 1000   624 Nov  7 12:29 bigfile.c
  55591102 -rw-rw-r--.  1 1000 1000   418 Nov  7 12:29 flen_stat.c
  55591103 -rw-rw-r--.  1 1000 1000   854 Nov  7 12:29 ftype-lstat.c
  55573484 -rw-rw-r--.  1 1000 1000   853 Nov  7 12:29 ftype.c
  55573485 -rw-rw-r--.  1 1000 1000  1052 Nov  7 12:29 glob.c
   1528787 drwxrwxrwx.  3 1000 1000   132 Nov  7 12:29 lnk
  55588413 -rw-rw-r--.  1 1000 1000  2954 Nov  7 12:29 mydu.c
  55591075 -rwxrwxr-x.  1 1000 1000 13880 Nov  9 20:20 myls
  55591078 -rw-rw-r--.  1 1000 1000  8251 Nov  9 21:32 myls.c
  55588415 -rw-rw-r--.  1 1000 1000   177 Nov  7 12:29 open_rwx.c
  55588414 -rw-rw-r--.  1 1000 1000  1014 Nov  7 12:29 opendir.c
  55588416 -rw-rw-r--.  1 1000 1000   102 Nov  7 12:29 pattern.c
  55588417 -rw-rw-r--.  1 1000 1000   348 Nov  7 12:29 suid.c
  55588418 -rw-rw-r--.  1 1000 1000   197 Nov  7 12:29 trunc.c
  55588419 -rw-rw-r--.  1 1000 1000   263 Nov  7 12:29 umask.c
  ```

  

- ####  
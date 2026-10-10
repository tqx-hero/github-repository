#### 信号signal：

##### 属于软中断。是操作系统针对突发事件给进程发送的一个提示信号。是一种进程间的异步通信机制。

##### 不同的信号在操作系统都会有默认的中断处理程序。可以提前定义进程对信号的处理程序，如果没有定义，OS会使用默认的处理程序处理这个信号。

##### 信号非常简单，携带的信息很少，是OS非常古老的通信方式。

###### 可通过trap -l或kill -l来查看Linux下的所有信号：

###### 具体文档可参考: man 7 signal

###### (1~31为用户层进程可使用的信号，也叫常规信号，34+均为内核层面使用的，称作实时信号)

```bash
#kill -l (trap -l)
#每个信号的数字都代表这个信号的号码，后面的单词都是信号的宏定义。
 1) SIGHUP       2) SIGINT       3) SIGQUIT      4) SIGILL       5) SIGTRAP
 6) SIGABRT      7) SIGBUS       8) SIGFPE       9) SIGKILL     10) SIGUSR1
11) SIGSEGV     12) SIGUSR2     13) SIGPIPE     14) SIGALRM     15) SIGTERM
16) SIGSTKFLT   17) SIGCHLD     18) SIGCONT     19) SIGSTOP     20) SIGTSTP
21) SIGTTIN     22) SIGTTOU     23) SIGURG      24) SIGXCPU     25) SIGXFSZ
26) SIGVTALRM   27) SIGPROF     28) SIGWINCH    29) SIGIO       30) SIGPWR
31) SIGSYS      34) SIGRTMIN    35) SIGRTMIN+1  36) SIGRTMIN+2  37) SIGRTMIN+3
38) SIGRTMIN+4  39) SIGRTMIN+5  40) SIGRTMIN+6  41) SIGRTMIN+7  42) SIGRTMIN+8
43) SIGRTMIN+9  44) SIGRTMIN+10 45) SIGRTMIN+11 46) SIGRTMIN+12 47) SIGRTMIN+13
48) SIGRTMIN+14 49) SIGRTMIN+15 50) SIGRTMAX-14 51) SIGRTMAX-13 52) SIGRTMAX-12
53) SIGRTMAX-11 54) SIGRTMAX-10 55) SIGRTMAX-9  56) SIGRTMAX-8  57) SIGRTMAX-7
58) SIGRTMAX-6  59) SIGRTMAX-5  60) SIGRTMAX-4  61) SIGRTMAX-3  62) SIGRTMAX-2
63) SIGRTMAX-1  64) SIGRTMAX
```

###### 各常规信号的说明如下：

```tex
1) SIGHUP 本信号在用户终端连接(正常或非正常)结束时发出,由该shell进程启动的所有子进程(包括shell进程)会被全部kill。默认：终止进程

2) SIGINT 程序终止(interrupt)信号, 在用户键入INTR字符(通常是Ctrl+C)时发出。默认：终止进程

3) SIGQUIT 和 SIGINT类似, 但由QUIT字符(通常是Ctrl+\)来控制. 进程在因收到 SIGQUIT 退出时会产生core文件, 在这个意义上类似于一个程序错误信号.
	默认：建立CORE文件终止进程

4) SIGILL 执行了非法指令. 通常是因为可执行文件本身出现错误, 或者试图执行数据段. 堆栈溢出时也有可能产生这个信号.默认：终止进程，建立CORE文件

5) SIGTRAP 由断点指令或其它trap指令产生. 由debugger使用.默认：建立CORE文件，跟踪自陷

6) SIGABRT 程序自己发现错误并调用abort时产生.默认：终止进程，建立CORE文件

6) SIGIOT 在PDP-11上由iot指令产生, 在其它机器上和SIGABRT一样.默认：建立CORE文件,执行I/O自陷

7) SIGBUS 非法地址, 包括内存地址对齐(alignment)出错. eg: 访问一个四个字长的整数, 但其地址不是4的倍数.默认：建立CORE文件,总线错误

8) SIGFPE 在发生致命的算术运算错误时发出. 不仅包括浮点运算错误, 还包括溢出及除数为0等其它所有的算术的错误.默认：建立CORE文件,浮点异常

9) SIGKILL 用来立即结束程序的运行. 本信号不能被阻塞, 处理和忽略.默认： 终止进程

10) SIGUSR1 留给用户使用。默认： 终止进程

11) SIGSEGV 试图访问未分配给自己的内存, 或试图往没有写权限的内存地址写数据(段错误).默认：建立CORE文件终止进程

12) SIGUSR2 留给用户使用。默认： 终止进程

13) SIGPIPE 管道破裂，当进程往没有开启读端的管道内部写入数据时触发。默认处理是终止进程。

14) SIGALRM 时钟定时信号, 计算的是实际的时间或时钟时间.计时器到时， alarm函数使用该信号.默认：终止进程

15) SIGTERM 程序结束(terminate)信号, 与SIGKILL不同的是该信号可以被阻塞和处理. 通常用来要求程序自己正常退出. shell命令kill缺省产生这个信号.
	默认：终止进程

17) SIGCHLD 子进程结束时, 父进程会收到这个信号.默认：忽略信号

18) SIGCONT 让一个停止(stopped)的进程继续执行. 本信号不能被阻塞. 可以用一个handler来让程序在由stopped状态变为继续执行时完成特定的工作. 例如, 重新显示提示符。默认：忽略信号

19) SIGSTOP 停止(stopped)进程的执行. 注意它和terminate以及interrupt的区别:该进程还未结束, 只是暂停执行. 本信号不能被阻塞, 处理或忽略.
	默认：停止进程

20) SIGTSTP 停止进程的运行, 但该信号可以被处理和忽略. 用户键入SUSP字符时(通常是Ctrl+Z)发出这个信号。默认：停止进程

21) SIGTTIN 当后台作业要从用户终端读数据时, 该作业中的所有进程会收到SIGTTIN信号. 缺省时这些进程会停止执行.默认：停止进程

22) SIGTTOU 类似于SIGTTIN, 但在后台进程写终端(或修改终端模式)时收到.默认：停止进程

23) SIGURG 有"紧急"I/O数据或out-of-band数据到达socket时产生.默认：忽略信号

24) SIGXCPU 超过CPU时间资源限制. 这个限制可以由getrlimit/setrlimit来读取/改变。默认：终止进程

25) SIGXFSZ 超过文件大小资源限制.默认：终止进程

26) SIGVTALRM 虚拟时钟信号. 类似于SIGALRM, 但是计算的是该进程占用的CPU时间，虚拟计数器到时触发.默认：终止进程

27) SIGPROF 类似于SIGALRM/SIGVTALRM, 但包括该进程用的CPU时间以及系统调用的时间，统计分布图用计时器到时触发.默认：终止进程

28) SIGWINCH 窗口大小改变时发出.默认：忽略信号

29) SIGIO 文件描述符准备就绪, 可以开始进行输入/输出操作.默认：忽略信号

30) SIGPWR 断电
31) SIGSYS     /* Bad system call.  */
```

##### SIGKILL与SIGSTOP不能被更改、捕获、阻塞以及忽略。

###### 每个信号都有默认的处理程序，默认处理程序包括：

```tex
Term  默认终止进程

Ign   默认忽略进程

Core   默认是终止进程并生成core文件(参见core(5))

Stop   默认暂停(停止)进程

Cont   如果当前进程处于暂停(停止)状态，恢复进程继续执行。
```

###### 当进程收到信号之前，可以通过注册信号的方式，给该进程注册相关的信号处理逻辑。当内核给该进程发送这个信号时，会按照注册的处理逻辑处理该信号(也就是函数回调)。

###### 如果没有给这个信号注册处理事件。内核会执行信号的默认处理程序，就是上面列表中的默认处理。

##### 内核对信号的实现原理(底层理解)：

##### 在进程的PCB结构体中有3个字段：信号位图signal、信号处理函数数组、信号阻塞集blocked

```c
struct task_struct {
/* these are hardcoded - don't touch */
        long signal;	//信号位图，信号值 = offset+1，例如：0号位代表1号信号，即SIGHUP
        struct sigaction sigaction[32]; //每个信号处理回调函数的数组，与信号位图对应，信号值 = 数组下标+1
        long blocked;   /* 信号阻塞集位图，置1的位代表这一位表示的信号被屏蔽 */
}
//信号处理函数结构体
struct sigaction {
        void (*sa_handler)(int);	//信号处理函数
        sigset_t sa_mask;	//信号的掩码，屏蔽集，表示执行当前信号时要屏蔽的信号集。处理函数返回时屏蔽自动撤销。
        int sa_flags;	//指定改变信号处理过程的信号集。
        void (*sa_restorer)(void);	//恢复函数指针，内核内部用来清理用户态的堆栈。
};
```

##### 当程序执行被内部或外部原因中断(硬中断或软中断)时，内核会根据中断类型给进程发送相关的中断标识(信号)，就会给进程的PCB的signal字段相关的那一位置1.

##### 当CPU切换到该进程执行时，查看signal字段哪一位置1，表示这个进程接收到了这个信号，再用这一位与阻塞集blocked做运算(&)，当&运算结果为0表示没有被阻塞，就会找到当前位所在sigaction数组的下标的那个sigaction结构体，查找到信号处理函数：sa_handler执行，同时恢复signal字段这一位为0;如果该信号被阻塞，signal这一位依旧保持1，直到blocked不屏蔽这一位的信号，在执行上面的处理流程。

##### 当用户指定某个信号的处理函数时，也就是改变的 sigaction[信号值-1]结构体中sa_handler这个函数指针，在信号触发时通过上述流程找到sa_handler，EIP寄存器重定向找到函数入口执行。

##### 正由于这个过程中信号是以位图的方式工作的，当一个信号被屏蔽时不会将那一位置0，后续如果再次出现这个信号时，当前位已经为1的情况下不能再次+1，导致同一个信号如果出现屏蔽情况在没有处理时再次发出，会出现信号覆盖的情况，现象就是屏蔽多次出现的同一信号在取消屏蔽后只会执行一次。*即信号不支持排队。*



#### 信号的相关API:

- ##### 发送信号kill(2):

- [ ] ###### 注意：超级用户可以给任意进程发送信号，普通用户不能给系统进程发送信号

```c
#include <sys/types.h>
#include <signal.h>
/**
	给一个或多个进程发送信号。
	pid: 进程id
		>0 : 给ID = pid的进程发送信号
		=0 : 给调用进程所在的组的所有进程发送信号
		=-1: 给所有进程(1号进程init除外)发送信号
		<-1: 给进程组id=|pid| 的所有进程发送信号
	sig: 信号数值
		取值0： 表示不发送任何信号
		>0 : 发送数值表示的信号
	return:
		0: 发送成功至少1个信号
		-1： 失败，errno为错误码
*/
int kill(pid_t pid, int sig);
```

##### demo1:给进程发送不同的信号，包括SIGINT、SIGKILL、SIGSTOP、SIGCONT、SIGTERM

###### 定义测试函数loop.c:

```c
#include <stdio.h>
#include <unistd.h>
//测试函数，输出进程ID，之后循环，等待其他进程发送SIGINT信号
int main(){
        printf("当前进程id = %d\n",getpid());
        while(1){
                printf("循环中...\n");
                sleep(1);
        }
        printf("程序被中断\n");
        return 0;
}
```

###### 定义信号发送函数kill.c:

```c
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
//给某个进程发送信号
#ifdef I
#define SIG SIGINT
#endif

#ifdef S
#define SIG SIGSTOP
#endif

#ifdef C
#define SIG SIGCONT
#endif

#ifdef K
#define SIG SIGKILL
#endif

#ifdef T
#define SIG SIGTERM
#endif
int main(int argc,char** argv){
        if(argc < 2){
                fprintf(stderr,"参数个数不足，应该包含: 进程号\n");
                return -1;
        }
        pid_t pid = atoi(argv[1]);;
        printf("输入的进程号 = %d\n",pid);
        printf("要发送的信号 = %d\n",SIG);
        if(kill(pid,SIG) == -1)
                perror("kill error");
        return 0;
}
```

##### 编译时可通过 -D选项来指定宏，产生不同的信号发送程序。

如通过：

```bash
gcc kill.c -o kill_int -DL
```

产生的是SIGINT信号的程序：kill_int，上述示例的宏定义可以生成5个信号发送程序。

有：kill_cont  kill_int  kill_kill  kill_stop  kill_term

###### 启动./loop，获得loop的进程号，通过执行如上的信号发送函数 + 进程号可给loop进程发送信号，查看其效果。

如查看SIGSTOP信号的效果，执行：

```bash
./kill_stop 140772	#140772为loop脚本的进程号
```

可看到loop程序状态为暂停：

```bash
tqx       140772  0.0  0.0   2496   576 pts/3    T    11:13   0:00 ./loop	#T为接收SIGSTOP信号后暂停状态标识。
```

执行 ./kill_cont 140772后，进程又继续执行：

```bash
tqx       140665  0.0  0.0   2496   576 pts/3    S    11:20   0:00 ./loop	#S为执行状态
```



- ##### raise(3):

  ###### 进程给自己发送信号，等价于kill(getpid(),sig);

  ```c
  #include <signal.h>
  
  int raise(int sig);
  ```

  ###### demo:子进程5s后给自己发送SIGTERM信号，父进程阻塞等待回收子进程PCB

  ```c
  #include <signal.h>
  #include <unistd.h>
  #include <stdio.h>
  #include <stdlib.h>
  #include <sys/wait.h>
  //raise()
  int main(){
          pid_t pid;
          if((pid = fork()) == -1){
                  perror("fork error");
                  exit(-1);
          }
          if(pid == 0){
                  sleep(5);
                  //5秒后子进程给自己发送终止信号
                  raise(SIGTERM);
                  printf("子进程给自己发送信号成功\n");
                  exit(0);
          }
          if(waitpid(pid,NULL,0) == -1)
                  perror("waitpid error");
          return 0;
  }
  ```

  

- ##### abort(3):

  ###### 给自己发送终止信号，并产生core文件，等价于 kill(getpid(),SIGABRT)。

  ```c
  #include <stdlib.h>
  
  void abort(void);
  ```

  demo:

  ```c
  #include <signal.h>
  #include <unistd.h>
  #include <stdio.h>
  #include <stdlib.h>
  #include <sys/wait.h>
  //abort()
  int main(){
          pid_t pid;
          if((pid = fork()) == -1){
                  perror("fork error");
                  exit(-1);
          }
          if(pid == 0){
                  sleep(3);
                  //3秒后子进程给自己发送终止信号
                  abort();
                  printf("子进程给自己发送信号成功\n");
                  exit(0);
          }
          if(waitpid(pid,NULL,0) == -1)
                  perror("waitpid error");
          return 0;
  }
  ```

  

- ##### alarm(3):

  ###### 进程给自身设置时钟，经过指定时间(单位：秒)后，内核会给该进程发送SIGALRM信号.由于进程调度问题，进程不一定在信号产生后立刻处理该信号。

  ###### 每个进程同一时刻只能设置1个alarm()，设置闹钟后进程会继续往后执行，不会阻塞。

  ###### 当闹钟响起时，内核会给进程发送信号，默认杀死进程，被正在挂起的进程也会被唤醒退出。

  ```c
  #include <unistd.h>
  /**
  	seconds:
  		参数设置0，会取消已挂起的alarm请求
  		>0 : 如果上次的alarm()还没发出信号，将以最新的alarm()进行覆盖。
  	return：
  		>0: 如果上次alarm()设置的时间还没到，返回上次闹钟响起的剩余时间。
  		=0: 除以上情况外。
  */
  unsigned alarm(unsigned seconds);
  ```

  ###### demo: 设置2秒的闹钟

  ```c
  #include <unistd.h>
  #include <stdio.h>
  
  int main(){
          printf("hello\n");
          alarm(2);
          printf("exit..\n");
          while(1);
          return 0;
  }
  ```

  输出：

  ```bash
  tqx@linux-ubuntu$ ./alarm
  hello
  exit..
  Alarm clock
  ```

  ###### demo:取消上面设定的闹钟：

  ```c
  #include <unistd.h>
  #include <stdio.h>
  //取消alarm()
  int main(){
          printf("hello\n");
          alarm(2);
          printf("exit..\n");
          alarm(0);	//设定闹钟时间为0
          while(1);
          return 0;
  }
  ```

  ###### demo：重新设置闹钟

  ```c
  #include <unistd.h>
  #include <stdio.h>
  //重新设置alarm()
  int main(){
          printf("hello\n");
          alarm(5);	//设定闹钟5s
          printf("exit..\n");
          sleep(2);	//挂起2s
          printf("%u\n",alarm(2));	//重新设定闹钟2s，返回值为3，代表之前的闹钟还有3s到时
          while(1);
          return 0;
  }
  ```

  

- ##### 修改信号处理程序sigaction(2)：

  ###### 不能修改SIGKILL与SIGSTOP信号的处理。

```c
#include <signal.h>
typedef unsigned long sigset_t;
typedef void (*__sighandler_t)(int);	//函数指针的参数为信号的编号
typedef struct siginfo siginfo_t;
/**
	signum: 信号的编号
	act: 要设置的信号处理相关配置
		SIG_IGN: ((__sighandler_t)  1) 表示忽略该信号
		SIG_DFL:  ((__sighandler_t)  0) 默认处理程序。
		自定义函数: 自定义信号的处理逻辑。
	oldact: 旧的信号处理相关配置。返回成功后会将覆盖之前的旧处理配置放到该地址，以便后续恢复。
	return：
		0： 成功。
		-1： 失败
*/
int sigaction(int signum, const struct sigaction *act,struct sigaction *oldact);

struct sigaction {
        union {
          __sighandler_t _sa_handler;//处理函数，取值有： 自定义函数指针、SIG_IGN、SIG_DFL。与sa_sigaction为联合体，二者只能取1
          void (*_sa_sigaction)(int, siginfo_t *, void *);//另一种函数处理，当sa_flags & SA_SIGINFO不为0时，启用该函数处理，否则启用sa_handler
        } _u;
        sigset_t sa_mask;//处理该信号时的屏蔽字。作用域仅信号处理期间，信号处理前后都不会生效。
        unsigned long sa_flags;//处理函数的选项。可通过 0 | 各比特位获得， 下面进行分类描述。
        void (*sa_restorer)(void);//内核内部使用的，用来恢复执行完回调函数后返回到原函数的堆栈信息。
};

//_sa_sigaction函数：
/**
	sig: 信号的编号
	info: 信号的更详细描述信息。结构体在下面解释。
	ucontext： 内核跳板函数。是进程被中断时内核对进程保存现场(堆栈、寄存器、PC等重要信息)压栈后的跳转地址。用户层用不到。
		作用就是当handler执行完成后，内核会调用sigreturn，该函数会对栈指针ESP进行更换，更换成这个地址，然后硬件弹栈，恢复现场，使其回到进程被信号中断之前的下一条指令继续执行。
*/
 void handler(int sig, siginfo_t *info, void *ucontext)
{
   ...
}

siginfo_t {
   int      si_signo;     /* Signal number */
   int      si_errno;     /* An errno value */
   int      si_code;      /* Signal code */
   int      si_trapno;    /* Trap number that caused
                             hardware-generated signal
                             (unused on most architectures) */
   pid_t    si_pid;       /* Sending process ID */
   uid_t    si_uid;       /* Real user ID of sending process */
   int      si_status;    /* Exit value or signal */
   clock_t  si_utime;     /* User time consumed */
   clock_t  si_stime;     /* System time consumed */
   sigval_t si_value;     /* Signal value，联合体类型，可以使用该字段当作参数传递给回调函数，进行异步处理 */
   int      si_int;       /* POSIX.1b signal */
   void    *si_ptr;       /* POSIX.1b signal */
   int      si_overrun;   /* Timer overrun count;
                             POSIX.1b timers */
   int      si_timerid;   /* Timer ID; POSIX.1b timers */
   void    *si_addr;      /* Memory location which caused fault */
   long     si_band;      /* Band event (was int in
                             glibc 2.3.2 and earlier) */
   int      si_fd;        /* File descriptor */
   short    si_addr_lsb;  /* Least significant bit of address
                             (since Linux 2.6.32) */
   void    *si_lower;     /* Lower bound when address violation
                             occurred (since Linux 3.19) */
   void    *si_upper;     /* Upper bound when address violation
                             occurred (since Linux 3.19) */
   int      si_pkey;      /* Protection key on PTE that caused
                             fault (since Linux 4.6) */
   void    *si_call_addr; /* Address of system call instruction
                             (since Linux 3.5) */
   int      si_syscall;   /* Number of attempted system call
                             (since Linux 3.5) */
   unsigned int si_arch;  /* Architecture of attempted system call
                             (since Linux 3.5) */
}

union sigval_t{
    int    sival_int;   // 传递整型
    void  *sival_ptr;   // 传递指针
}
```

##### sa_flags选项：

```c
/**
1、SA_NOCLDSTOP： 	
    #define       SA_NOCLDSTOP  1
	仅信号为SIGCHLD时生效。
	子进程停止（收到 SIGSTOP/SIGTSTP/SIGTTIN/SIGTTOU）或恢复运行（收到 SIGCONT）时，不向父进程发送 SIGCHLD 通知。

2、SA_NOCLDWAIT（Linux 2.6+）:	
	#define SA_NOCLDWAIT  2
	信号为SIGCHLD时，启用该选项，子进程退出不会变成僵尸进程，内核会自动回收子进程的资源，而不需要父进程wait/waitpid回收。
	该标志尽在设置SIGCHLD处理函数，或者SIGCHLD处理函数为SIG_DFL时有效。
	注意，POSIX标准没有规定该选项启用时子进程退出时是否还会给父进程发送SIGCHLD信号，不同系统不一致，需要注意可移植性。但是在Linux系统中启用该选项依旧会发送SIGCHLD。

3、SA_NODEFER:
	# define SA_NODEFER   0x40000000
	该信号在信号处理函数执行期间，不会屏蔽自身的信号。仅在注册信号处理函数时生效。
	不启用该选项时，进入handler时，内核会把当前信号默认加入屏蔽字，阻塞本身，以防止递归调用。
	启用选项后：
		handler执行过程中，同一种信号可以再次递达，再次进入handler，产生递归，容易导致栈溢出，慎用。
		
4、SA_RESETHAND：
	# define SA_RESETHAND 0x80000000
	当信号函数被调用一次，立即将该信号重置为默认行为，就是自定义的信号函数仅使用一次就恢复默认。仅注册handler生效。
5、SA_RESTART:
	# define SA_RESTART   0x10000000
	采用BSD信号语义：
		被该信号中断的某些系统调用，在handler返回后自动重新执行。支持的系统调用参考signal(7)。
		慢系统调用(read/write/accept/pause等)被信号打断时，会返回-1，errno = EINTR，启用该选项后，该信号的处理函数执行完成，内核会自动重启这个系统调用，不会返回EINTR。
		如果不启用该选项，或者系统调用不支持该选项，被信号中断时会返回 -1，errno = EINTR。
	能够被内核重启的系统调用有：
		1、慢设备的：read (2), readv (2), write (2), writev (2), ioctl (2)。其中慢设备是I/O调用可能导致无限期阻塞的，如中断、管道、socket等。
	如果慢速设备 IO 在被信号打断前已经传输了一部分数据：调用返回成功，返回已经传输的字节数，而不是 EINTR。
	本地磁盘不属于 slow 设备；磁盘 IO不会被信号中断。
		2、open(2)、wait(2)系列。
		3、Socket接口：accept (2), connect (2), recv (2), recvfrom (2), recvmmsg (2), recvmsg (2), send (2), sendto (2), sendmsg (2)
		注意：socket 设置了超时（SO_RCVTIMEO / SO_SNDTIMEO）时，SA_RESTART 不再生效！
		4、文件锁：flock (2) 以及 fcntl (2) 的 F_SETLKW、F_OFD_SETLKW	LKW = lock wait，阻塞式文件锁。
		5、POSIX消息队列（不是System V IPC的消息队列msg系列,msg系列不会重启！）mq：
			mq_receive (3), mq_timedreceive (3), mq_send (3), mq_timedsend (3)
		6、futex (2) FUTEX_WAIT（Linux2.6.22 之后；旧版本永远返回 EINTR）、FUTEX_WAIT_BITSET
		7、getrandom(2)
		8、pthread_mutex_lock (3), pthread_cond_wait (3) 以及相关 API。条件变量等待、互斥锁阻塞获取。pthread 同步原语，支持 SA_RESTART。
		9、POSIX 信号量 sem_wait (3), sem_timedwait (3)（Linux2.6.22 之后；旧版本永远 EINTR）
			注意是：POSIX semaphore（sem_t），不是 System V semop！semop 属于 System V，SA_RESTART 无效。
		10、inotify 文件描述符上的 read (2)（Linux3.8 之后；旧版本永远 EINTR）
6、SA_SIGINFO：
	#define SA_SIGINFO 0x00000004
	开启选项：使用struct sigaction中的sa_sigaction函数；
	不开启：默认使用sa_handler
*/
```



###### demo:

```c
#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//第一个循环的标志位
int flag;
//修改SIGINT信号的处理逻辑
void sigint_handler(int signum){
        printf("SIGINT 信号被发送过来了 ,num = %d\n",signum);
        flag = 0;	//将标志位置0，停止第一个循环。
}
int main(){
        flag = 1;
        struct sigaction sat,oldsat;	//定义新旧处理逻辑的结构体
        bzero(&sat,sizeof(sat));
        sat.sa_handler = sigint_handler;
        sigaction(SIGINT,&sat,&oldsat);	//注册SIGINT驱动事件。
        while(flag){
                printf("正在循环1...\n");
                sleep(1);
        }
        //SIGINT信号处理完成后，恢复其默认信号
        sigaction(SIGINT,&oldsat,NULL);
        while(1){
                printf("正在循环2...\n");
                sleep(1);
        }
        return 0;
}
```

###### demo2:使用sa_sigaction()函数：

```c
#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//使用sa_sigaction()处理
int flag;
void act_handler(int signum,siginfo_t * info,void* ucontext){
        printf("信号编号 = %d\n",signum);
//      printf("传入的参数 = %d\n",info->si_value);	//注意：该参数只能在某些信号中传入参数，SIGINT、SIGCHLD、SIGEGV不会填充。
        flag = 0;
}

int main(){
        flag = 1;
        struct sigaction act;
        sigemptyset(&act.sa_mask);
        act.sa_sigaction = act_handler;
        act.sa_flags = SA_SIGINFO | SA_RESETHAND; //设置信号处理函数为sa_sigaction()，并且只执行一次。
        sigaction(SIGINT,&act,NULL);
        while(flag){
                printf("1...\n");
                sleep(1);
        }
        while(1){
                printf("2..\n");
                sleep(1);
        }
        return 0;
}
```

执行结果：

```bash
tqx@linux-ubuntu$ ./sig_action_func
1...	#这是第一个while循环
1...
1...
1...
1...
1...
^C信号编号 = 2 #ctrl+c后进入act_handler，将flag设置为0，第一个while跳出。
2..	#进入第二个循环。。由于有SA_RESETHAND选项，此时处理函数初始化为默认。
2..
2..
2..
2..
^C	#执行SIGINT的默认处理，也就是终止进程。
```



- ##### signal(2):

  ###### 更古老版本的sigaction(2)

  ```c
  #include <signal.h>
  
  typedef void (*__sighandler_t)(int);
  //如果要显式使用 sighandler_t 类型，必须添加宏定义： #define _GNU_SOURCE
  #define _GNU_SOURCE
  typedef __sighandler_t sighandler_t;
  /**
  	signum: 要设置的信号编号。
  	handler: 信号处理函数。同样可取三个值
  		SIG_IGN: 忽略信号
  		SIG_DFL： 默认信号处理(参考man 7 signal)
  		自定义函数： 自定义的信号处理逻辑
  	return:
  		成功： 返回覆盖之前的信号处理配置的函数地址。第一次成功设置后返回的是SIG_DFL，也就是(void*)0 =NULL
  		失败： 返回SIG_ERR ： ((__sighandler_t)-1)，错误码在errno
  */
  __sighandler_t signal(int signum, __sighandler_t handler);
  ```

  demo：同sigaction一样的效果

  ```c
  #define _GNU_SOURCE
  #include <signal.h>
  #include <unistd.h>
  #include <stdio.h>
  #include <stdlib.h>
  #include <string.h>
  
  int flag;
  //修改SIGINT信号的处理逻辑
  void sigint_handler(int signum){
          printf("SIGINT 信号被发送过来了 ,num = %d\n",signum);
          flag = 0;
  }
  int main(){
          flag = 1;
          sighandler_t old_hdr;
          old_hdr = signal(SIGINT,sigint_handler);	//保存返回的默认处理函数
          while(flag){
                  printf("正在循环1...\n");
                  sleep(1);
          }
          printf("old handler = %d\n",(old_hdr == SIG_DFL));	//输出覆盖之前的处理函数等于SIG_DFL
          //SIGINT信号处理完成后，恢复其默认信号
          signal(SIGINT,old_hdr);
          while(1){
                  printf("正在循环2...\n");
                  sleep(1);
          }
          return 0;
  }
  ```

  

- 

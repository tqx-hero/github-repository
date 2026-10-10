#### 消息队列：

- ##### 生成消息队列的唯一标识key(man 3 ftok):

  ```c
  #include <sys/ipc.h>
  /**
  	利用文件名与签名生成消息队列的唯一标识key
  	pathname: 文件名称，文件必须存在
  	proj_id: 签名
  	return:
  		-1: 生成失败，错误码errno
  		非-1：成功，返回唯一标识(标识为有符号32位整数)
  */
  key_t ftok(const char *pathname, int proj_id);
  typedef int key_t;
  ```

  ###### demo:

  ```c
  #include <sys/ipc.h>
  #include <stdio.h>
  
  int main(){
          key_t kt = ftok("./",186);
          if(kt == -1){
                  perror("ftok error");
                  return -1;
          }
          printf("kt = %d\n",kt);
          return 0;
  }
  ```

  

- ##### 创建消息队列(man 2 msgget):

  ```c
  #include <sys/msg.h>
  /**
  	创建消息队列
  	key: ftok()生成的唯一标识
  	msgflag: 消息队列的权限
  		IPC_CREAT: 当消息队列不存在时会进行创建。
  			如果 | IPC_EXCL,当消息队列已经存在时会报错，没有位或，消息队列存在，则会忽略IPC_CREAT。
  		IPC_EXCL: 检测消息队列是否存在。
  		
  		除了添加IPC_CREAT，必须给消息队列添加权限，(与open系统调用的权限相同，但是没有可执行权限，所以可以位或读写权限),例如： IPC_CREAT | 0666，标识该消息队列对所有用户都是读写权限，不存在则创建，存在则打开。
  		
  	return:
  		-1: 创建失败。
  		非负数: 创建成功，返回值为消息队列的标识。
  */
  int msgget(key_t key, int msgflg);
  ```

  ###### demo:

  ```c
  #include <sys/ipc.h>
  #include <stdio.h>
  #include <sys/msg.h>
  //创建消息队列
  int main(){
          key_t kt = ftok("./",186);
          if(kt == -1){
                  perror("ftok error");
                  return -1;
          }
          printf("kt = %d\n",kt);
          int msg_id = msgget(kt,IPC_CREAT | 0666);
          if(msg_id == -1){
                  perror("msgget error");
                  return -1;
          }
          printf("消息队列的id = %d\n",msg_id);
          return 0;
  }
  ```

  ###### 结果：

  ```bash
  tqx@LAPTOP-G3KT1I3B$ ./msgget
  kt = -1171240844
  消息队列的id = 0
  tqx@LAPTOP-G3KT1I3B$ ipcs -q
  
  ------ Message Queues --------
  key        msqid      owner      perms      used-bytes   messages
  0xba304874 0          tqx        666        0            0
  ```

  

- ##### 发送消息：

  ```c
  #include <sys/msg.h>
  /**
  	msgid: 消息队列id
  	msgp: 要发送的消息结构体地址。
  	msgsz: 发送的消息正文大小。注意，该大小不包括消息结构体的第一个字段mtype
  	msgflg: 当队列已满时如何处理
  		0：阻塞直到满足条件
  		IPC_NOWAIT： 不阻塞直接返回。
  	return:
  		-1: 发送失败
  		0: 发送成功
  */
  int msgsnd(int msqid, const void* msgp, size_t msgsz,int msgflg);
  
  //消息结构体命名格式：
  struct my_message{
    	long int mtype; //消息类型，值必须大于0，用于msgrcv()读取时指定读取类型。必有选项。
      char buf[n]; 	//消息体。可根据自身需求定义为指针、数组等多项内容。
      ...;			
  };
  ```

  ###### demo1:将hello world打包发送到消息队列的链表节点中

  ```c
    1 #include <sys/msg.h>
    2 #include <stdio.h>
    3 #include <string.h>
    4 #include <unistd.h>
    5 #include <stdlib.h>
    6 //msgsnd()函数发送消息
    7
    8 typedef struct {
    9         long int mtype;	//长整型，用于标识读取消息时的标志，不可缺
   10         char buf[128];	//消息体
   11 } msg_t;
   12
   13 int main(){
   14         key_t kt = ftok("./",186);
   15         if(kt == -1){
   16                 perror("ftok error");
   17                 exit(-1);
   18         }
   19         int msg_id = msgget(kt,IPC_CREAT | 0666);
   20         if(msg_id == -1){
   21                 perror("msgget error");
   22                 exit(-1);
   23         }
   24         msg_t message;
   25         message.mtype = 1;
   26         sprintf(message.buf,"%s","hello world!");
   27         fprintf(stdout,"要发送的消息 = %s\n",message.buf);
   28         if(msgsnd(msg_id,&message,sizeof(message) - sizeof(message.mtype),IPC_NOWAIT) == -1){
   29                 perror("msgsnd msg error");
   30                 exit(-1);
   31         }
   32         return 0;
   33 }
  ```

  ###### 发送到消息队列后：

  ```bash
  tqx@LAPTOP-G3KT1I3B$ ipcs -q
  
  ------ Message Queues --------
  key        msqid      owner      perms      used-bytes   messages
  0xba304874 2          tqx        666        128          1
  ```

  

- ##### 接收消息：

  ```c
  #include <sys/msg.h>
  /**
  	msqid: 消息队列id
  	msgp: 把消息读到的内存地址
  	msgsz: 消息正文大小，不包括msg_type
  	msgtyp: 要读取的消息体的类型，消息体结构体的第一个字段。
  		 =0: 读取队列的第一个消息
  		 >0: 读取这个类型对应的消息
  		 <0: 读取类型小于或等于该绝对值的消息。若有若干个消息，读取类型值最小的那条。
  	msgflg: 读取队列时的行为
  		0：队列为空时阻塞直到接收到消息
  		IPC_NOWAIT： 不阻塞直接返回。没收到消息直接返回-1，errno = ENOMSG
  		MSG_NOERROR: 如果消息本身字节数比要放入结构体msgp的容量更大，则会截断消息装满msgp最大容量，不通知消息发送进程。
  		
  	return :
  		-1: 接收失败，errno为错误码
  		非负数：
  			拷贝到msgp内存的真实字节数
  */
  ssize_t msgrcv(int msqid, void msgp[.msgsz], size_t msgsz, long msgtyp,
                 int msgflg);
  ```

  ###### demo1:读取上述msgsnd队列中消息体数据

  ```c
    1 #include <sys/msg.h>
    2 #include <stdio.h>
    3 #include <string.h>
    4 #include <unistd.h>
    5 #include <stdlib.h>
    6 //msgrcv()函数接收消息
    7
    8 typedef struct {
    9         long int mtype;
   10         char buf[128];
   11 } msg_t;
   12
   13 int main(){
   14         key_t kt = ftok("./",186);
   15         if(kt == -1){
   16                 perror("ftok error");
   17                 exit(-1);
   18         }
   19         int msg_id = msgget(kt,IPC_CREAT | 0666);
   20         if(msg_id == -1){
   21                 perror("msgget error");
   22                 exit(-1);
   23         }
   24         msg_t message;
   25         if(msgrcv(msg_id,&message,sizeof(message) - sizeof(message.mtype),1,IPC_NOWAIT) == -1){
   26                 perror("msgsnd msg error");
   27                 exit(-1);
   28         }
   29         fprintf(stdout,"接收到的数据类型 = %ld\n",message.mtype);
   30         fprintf(stdout,"接收到的数据 = %s\n",message.buf);
   31         return 0;
   32 }
  ```

  ###### 从消息队列读取数据后：

  ```bash
  tqx@LAPTOP-G3KT1I3B$ ./msgrcv
  接收到的数据类型 = 1
  接收到的数据 = hello world!
  
  tqx@LAPTOP-G3KT1I3B$ ipcs -q
  
  ------ Message Queues --------
  key        msqid      owner      perms      used-bytes   messages
  0xba304874 2          tqx        666        0            0
  ```

  ###### demo2:定义消息结构体，cmd输入参数指定要发送接收的消息类型

  ###### 消息结构体 msg_t.h:

  ```c
    1 #ifndef __MSG_T_H
    2 #define __MSG_T_H
    3 //定义消息结构体
    4 typedef struct{
    5         long int mtype; //消息类型
    6         pid_t pid;      //发送方进程ID
    7         char msg_buf[128]; //消息内容
    8 }msg_t;
    9
   10 #endif
  ```

  ###### 发送消息 msgsnd.c:

  ```c
    1 #include <stdio.h>
    2 #include <sys/msg.h>
    3 #include <stdlib.h>
    4 #include <unistd.h>
    5 #include "msg_t.h"
    6 //msgsnd()发送消息
    7 //argv[1]为要发送的消息类型
    8 int main(int argc,char** argv){
    9         if(argc < 2){
   10                 fprintf(stderr,"请输入发送消息的类型\n");
   11                 exit(-1);
   12         }
   13         //生成消息队列的key
   14         key_t kt = ftok("./",1);
   15         if(kt == -1){
   16                 perror("ftok error");
   17                 exit(-1);
   18         }
   19         char* kptr = (char*) &kt;
   20         fprintf(stdout,"消息队列的key = %.2x%.2x%.2x%.2x\n",kptr[3],kptr[2],kptr[1],kptr[0]);//小端序，字节序为高高低低
   21         //创建/获取消息队列id
   22         int msg_id = msgget(kt,IPC_CREAT | 0666);
   23         if(msg_id == -1){
   24                 perror("msgget error");
   25                 exit(-1);
   26         }
   27         printf("消息队列ID = %d\n",msg_id);
   28         msg_t msg;
   29         msg.pid = getpid();	//填入进程ID
   30         msg.mtype = atol(argv[1]); //消息类型字符串转化为long int整型
   31         fprintf(stdout,"请输入要发送的消息: ");
   32         fflush(stdout);
   33         fgets(msg.msg_buf,sizeof(msg.msg_buf),stdin);
   34         if(msgsnd(msg_id,&msg,sizeof(msg) - sizeof(msg.mtype),IPC_NOWAIT) == -1){
   35                 perror("msgsnd error");
   36                 exit(-1);
   37         }
   38         fprintf(stdout,"消息发送成功\n");
   39         return 0;
   40 }
  ```

  ###### 接收消息 msgrcv.c:

  ```c
    1 #include <unistd.h>
    2 #include <sys/msg.h>
    3 #include <stdio.h>
    4 #include <stdlib.h>
    5 #include "msg_t.h"
    6 #include <errno.h>
    7 //msgrcv()接收消息
    8 //argv[1]为要接收的消息类型:
    9 // argv[1] == 0 : 无条件接收消息队列的第一条消息
   10 //argv[1] > 0 : 接收msg_t.mtype ==  argv[1]的消息
   11 //argv[1] < 0 : 接收满足 msg_t.mtype <= |argv[1]|所有消息中mtype最小的那一条
   12 int main(int argc,char** argv){
   13         if(argc < 2){
   14                 fprintf(stderr,"请输入用于接收的消息类型\n");
   15                 exit(-1);
   16         }
   17         key_t kt;
   18         int msg_id;
   19         ssize_t nbytes;
   20         //同样需要使用ftok()、msgget()函数获取消息队列的ID
   21         kt = ftok("./",1);
   22         if(kt == -1){
   23                 perror("ftok error");
   24                 exit(-1);
   25         }
   26         msg_id = msgget(kt,IPC_CREAT | 0666);
   27         if(msg_id == -1){
   28                 perror("msgget error");
   29                 exit(-1);
   30         }
   31         msg_t msg;
   32         nbytes = msgrcv(msg_id,&msg,sizeof(msg) - sizeof(msg.mtype),atol(argv[1]),IPC_NOWAIT);
   33         if(nbytes == -1){
   34                 //没读到消息，提示，否则输出错误
   35                 if(errno == ENOMSG){
   36                         fprintf(stdout,"队列中无该类型消息\n");
   37                         return 0;
   38                 }
   39                 perror("msgrcv error");
   40                 exit(-1);
   41         }
   42         fprintf(stdout,"消息发送进程ID : %d\n",msg.pid);
   43         fprintf(stdout,"消息类型 : %ld\n",msg.mtype);
   44         fprintf(stdout,"消息内容 : %s\n",msg.msg_buf);
   45         return 0;
   46 }
  ```

  ##### demo3:使用一个消息队列实现一对多聊天

  ###### **启动程序时的输入参数有2个，第一个argv[1]是自身的用户名，第二个参数argv[2]是绑定自身的mtype。**

  ###### fork()用于创建子进程，每个会话有2个进程分别负责读写消息队列。

  ###### 读消息队列就是按照msgrcv()定义读

  ###### 写消息队列时，先提前写入固定的字段：pid与username，至于mtype需要用户在每次发送消息时填入，用来区分给哪个用户发送这条消息。

  ###### 为简单起见，这里提示语直接写死了，扩展的话可以使用一个哈希表存储用户名与mtype的关系。

  ###### 此demo没有处理父子进程出错误退出时的流程，会导致子进程变成孤儿进程或僵尸进程，需要通过信号进行完善。

  ###### 1、第一种方式：

  ###### 启动脚本时输入相关参数。如： ./chat Lucy 1

  ###### 仅生成一份可执行程序，根据传参不同来启动不同的会话。

  ```c
    1 #include <sys/msg.h>
    2 #include <unistd.h>
    3 #include <fcntl.h>
    4 #include <stdio.h>
    5 #include <stdlib.h>
    6 #include <string.h>
    7 //使用消息队列实现多人聊天
    8 //fork()出子进程，父进程用于写消息，子进程用于读消息
    9 //封装消息结构体，除了mtype之外，消息正文有进程ID，用户名称、消息内容
   10 //创建/开启一个消息队列，使用消息队列读写函数进行系统调用
   11 //为简单起见，令argv[1] 为自身的用户名，argv[2]为消息类型
   12
   13 typedef struct {
   14         long int mtype;
   15         pid_t pid;
   16         char username[64];
   17         char msg_buf[256];
   18 }msg_t;
   19
   20 int main(int argc,char** argv){
   21         if(argc < 3){
   22                 fprintf(stderr,"参数必须包含:用户名、消息类型\n");
   23                 return -1;
   24         }
   25         int msg_id;
   26         key_t kt;
   27         pid_t pid;
   28         ssize_t nbytes;
   29         //创建、打开消息队列
   30         kt = ftok("./",1);
   31         if(kt == -1){
   32                 perror("ftok error");
   33                 exit(-1);
   34         }
   35         msg_id  = msgget(kt,IPC_CREAT | 0666); //根据key获取消息队列ID
   36         //定义消息结构体
   37         msg_t msg;
   38         //fork()子进程
   39         if((pid = fork()) == -1){
   40                 perror("fork error");
   41                 exit(-1);
   42         }
   43         //子进程负责读取消息到消息体
   44         if(pid == 0){
   45                 while(1){
   46                         nbytes = msgrcv(msg_id,&msg,sizeof(msg) - sizeof(long int),atol(argv[2]),0);
   47                         if(nbytes == -1){
   48                                 perror("msgrcv error");
   49                                 exit(-1);
   50                         }
   51                         //拼接读到的消息
   52                         fprintf(stdout,"mtype:[%ld],PID:[%d],username[%s]:%s\n",msg.mtype,msg.pid,msg.username,msg.msg_buf);
   53                 }
   54         }else{
   55                 //打包msg，填上固定字段username与pid
   56                 strcpy(msg.username,argv[1]);
   57                 msg.pid = getpid();
   58                 while(1){
   59                         //父进程写入消息，注意要添加给谁发送的消息
   60                         printf("请输入写入的消息类型mtype与消息内容msg，以空格分开(1:bob;2:join;3:jan):\n");
   61                         scanf("%ld %s",&msg.mtype,msg.msg_buf);
   62                         //发送消息
   63                         if(msgsnd(msg_id,&msg,sizeof(msg) - sizeof(long),0) == -1){
   64                                 perror("msgsnd error");
   65                                 break;
   66                         }
   67                 }
   68         }
   69         return 0;
   70 }
  ```

  ###### 2、第二种方式：使用宏在编译器进行脚本生成。gcc chat.c -Dp -o *_chat,利用-D选项的指定宏名称，生成不同的可执行程序分别启动。

  ```c
    1 #include <sys/msg.h>
    2 #include <unistd.h>
    3 #include <fcntl.h>
    4 #include <stdio.h>
    5 #include <stdlib.h>
    6 #include <string.h>
    7 //使用消息队列实现多人聊天
    8 //fork()出子进程，父进程用于写消息，子进程用于读消息
    9 //封装消息结构体，除了mtype之外，消息正文有进程ID，用户名称、消息内容
   10 //创建/开启一个消息队列，使用消息队列读写函数进行系统调用
   11 //定义宏，根据编译时 -D传入的宏不同来区分不同的名称.
   12 #ifdef L
   13 #define NAME 'L'
   14 char writer[]= "Lucy";
   15 #endif
   16
   17 #ifdef B
   18 #define NAME 'B'
   19 char writer[]= "Bob";
   20 #endif
   21
   22 #ifdef J
   23 #define NAME 'J'
   24 char writer[]= "Join";
   25 #endif
   26
   27 typedef struct {
   28         long int mtype;
   29         pid_t pid;
   30         char username[64];
   31         char msg_buf[256];
   32 }msg_t;
   33
   34 int main(int argc,char** argv){
   35         /*
   36         if(argc < 3){
   37                 fprintf(stderr,"参数必须包含:用户名、消息类型\n");
   38                 return -1;
   39         }
   40         */
   41         int msg_id;
   42         key_t kt;
   43         pid_t pid;
   44         ssize_t nbytes;
   45         //创建、打开消息队列
   46         kt = ftok("./",1);
   47         if(kt == -1){
   48                 perror("ftok error");
   49                 exit(-1);
   50         }
   51         msg_id  = msgget(kt,IPC_CREAT | 0666); //根据key获取消息队列ID
   52         //定义消息结构体
   53         msg_t msg;
   54         //fork()子进程
   55         if((pid = fork()) == -1){
   56                 perror("fork error");
   57                 exit(-1);
   58         }
   59         //子进程负责读取消息到消息体
   60         if(pid == 0){
   61                 while(1){
   62                         nbytes = msgrcv(msg_id,&msg,sizeof(msg) - sizeof(long int),(long int)(NAME),0);
   63                         if(nbytes == -1){
   64                                 perror("msgrcv error");
   65                                 exit(-1);
   66                         }
   67                         //拼接读到的消息
   68                         fprintf(stdout,"mtype:[%ld],PID:[%d],username[%s]:%s\n",msg.mtype,msg.pid,msg.username,msg.msg_buf);
   69                 }
   70         }else{
   71                 //打包msg，填上固定字段username与pid
   72                 strcpy(msg.username,writer);
   73                 msg.pid = getpid();
   74                 char snd_buf[256],ch;
   75                 while(1){
   76                         //父进程写入消息，注意要添加给谁发送的消息
   77                         printf("请输入要发送的人员首字母与消息内容msg，以:分开(如给Bob发送消息hello输入: [B:hello]):\n");
   78                         scanf("%c:%s",&ch,snd_buf);
   79                         //解析内容
   80                         msg.mtype = (long int)ch;
   81                         strcpy(msg.msg_buf,snd_buf);
   82                         //发送消息
   83                         if(msgsnd(msg_id,&msg,sizeof(msg) - sizeof(long),0) == -1){
   84                                 perror("msgsnd error");
   85                                 break;
   86                         }
   87                 }
   88         }
   89         return 0;
   90 }
  ```

  ###### 生成启动脚本 make.sh:

  ```bash
    1 #1/bin/bash
    2 # 生成聊天程序的脚本
    3 src="three_chat_define.c"
    4 names=("Join" "Bob" "Lucy");
    5 find . -name "*_chat" -type f -exec rm -rf {} +
    6 for item in "${names[@]}";do
    7         gcc -g $src -D${item:0:1} -o ${item}_chat
    8         echo "已生成可执行程序: ${item}_chat"
    9 done
  ```

  

- ##### msgctl(man 2 msgctl):用于对消息队列进行属性操作

  ```c
  #include <sys/types.h>
  #include <sys/ipc.h>
  #include <sys/msg.h>
  /**
  	对消息队列的属性进行设置，包括查询、修改、删除
  	msqid : 消息队列ID
  	cmd: 对消息队列的操作,取值如下:
  	
  		IPC_RMID: 立即删除该消息队列，唤醒所有处于等待状态的读进程与写进程（调用将返回错误，同时将错误号设置为 EIDRM）。调用进程必须具备相应权限，或者其有效用户 ID 需要与该消息队列的创建者或所有者的用户 ID 一致。此种情况下，msgctl () 的第三个参数会被忽略。
  		
  		IPC_STAT: 获取消息队列的属性，并将其拷贝到第三个参数表示的地址中
  		
  		IPC_SET:  将 buf 所指向的 msqid_ds 结构体中部分成员的值写入与此消息队列相关的内核数据结构，同时更新该结构体的 msg_ctime 成员。会更新该结构体的以下成员：msg_qbytes、msg_perm.uid、msg_perm.gid 以及 msg_perm.mode（其低 9 位）。调用进程的有效用户 ID 必须与该消息队列的所有者（msg_perm.uid）或者创建者（msg_perm.cuid）相匹配，或者调用者必须拥有特权。若要将 msg_qbytes 的值提升至超过系统参数 MSGMNB，则需要具备相应权限（Linux：CAP_SYS_RESOURCE 权限）。
  		struct ipc_perm中可以进行修改的属性有：
          struct ipc_perm {
              uid_t          uid;         // 属主的uid
              gid_t          gid;         // 属主的组id
              unsigned short mode;        // 权限
          };
  		
  		IPC_INFO:(ipcs -l)包括消息队列、共享内存、信号量数组等所有内核配置.
  			返回由 buf 指向的结构体中关于系统范围内消息队列限制与参数的信息。该结构体类型为 msginfo（因此需要进行强制类型转换）。使用时必须添加宏定义： #define _GNU_SOURCE。
  			
  		MSG_INFO(LINUX特有):(ipcs -q关于消息队列的一些系统配置)
  			返回一个 msginfo 结构体(需要强转成struct myqid_ds* 接收)，其中包含与 IPC_INFO 相同的信息，但以下字段会返回关于消息队列所占用系统资源的相关信息：msgpool 字段返回系统当前已存在的消息队列数量；msgmap 字段返回系统上所有队列中的消息总数；msgtql 字段返回所有队列内全部消息的总字节数。
  			
  		虽然MSG_INFO与IPC_INFO返回结构体都是msginfo,但是语义不同。
  		IPC_INFO返回的字段是包括内核维护的消息队列、共享内存、信号量等数据的全局配置信息；
  		MSG_INFO返回的是仅包括消息队列这一项的配置信息。
  		
  	buf: 对消息队列处理时的数据来源、去向
  	return: 
  		-1: 处理失败
  		0: 处理成功
  */
  int msgctl(int msqid, int cmd, struct msqid_ds *buf);
  //参数的结构体定义：
  struct msqid_ds {
      struct ipc_perm msg_perm;     /* Ownership and permissions */
      time_t          msg_stime;    /* Time of last msgsnd(2) */
      time_t          msg_rtime;    /* Time of last msgrcv(2) */
      time_t          msg_ctime;    /* Time of last change */
      unsigned long   __msg_cbytes; /* 当前队列中消息的字节数 */
      msgqnum_t       msg_qnum;     /* 队列中当前的消息数量 */
      msglen_t        msg_qbytes;   /* 队列可允许的最大字节数 */
      pid_t           msg_lspid;    /* 最后一次调用msgsnd(2)的进程ID */
      pid_t           msg_lrpid;    /* 最后一个调用msgrcv(2)的进程ID */
  };
  
  struct ipc_perm {
      key_t          __key;       /* 提供给msgget(2)的key */
      uid_t          uid;         /* 属主的uid */
      gid_t          gid;         /* 属主的组id */
      uid_t          cuid;        /* 创建者的uid */
      gid_t          cgid;        /* 创建者的组id */
      unsigned short mode;        /* 权限 */
      unsigned short __seq;       /* 序列号 */
  };
  
  struct msginfo {
      int msgpool; /* 用于存放消息数据的缓冲池大小（单位：基二进制千字节）；在内核中未使用 */
      int msgmap;  /* 消息映射表中的最大条目数；内核内部未使用 */
      int msgmax;  /* 单条消息可写入的最大字节数 */
      int msgmnb;  /* 可写入队列的最大字节数；用于在队列创建（msgget (2)）过程中初始化 msg_qbytes */
      int msgmni;  /* 最大消息队列数量 */
      int msgssz;  /* 消息段大小；内核内部未使用 */
      int msgtql;  /* 系统中所有队列的消息最大数量；内核内部未使用 */
      unsigned short int msgseg;
      /* Maximum number of segments;
                                        unused within kernel */
  };
  ```

  ##### cmd:

  ###### IPC_RMID:删除这个ID的消息队列

  ```c
    1 #include <unistd.h>
    2 #include <sys/types.h>
    3 #include <sys/ipc.h>
    4 #include <sys/msg.h>
    5 #include <stdio.h>
    6 #include <stdlib.h>
    7 //msgctl()系统调用对消息队列本身的操作
    8 //这里先以简单的删除消息队列为例
    9 int main(){
   10         if(msgctl(0,IPC_RMID,NULL) == -1){
   11                 perror("msgctl rm msg error");
   12                 exit(-1);
   13         }
   14         fprintf(stdout,"删除成功\n");
   15         execlp("ipcs","ipcs","-q",NULL);
   16         perror("exec ipcs error");
   17         return 0;
   18 }
  ```

  ###### IPC_STAT:获取消息队列的属性

  ```c
    1 #include <unistd.h>
    2 #include <sys/types.h>
    3 #include <sys/ipc.h>
    4 #include <sys/msg.h>
    5 #include <stdio.h>
    6 #include <stdlib.h>
    7 #include <string.h>
    8 //msgctl()获取消息队列的属性
    9 int main(){
   10         struct msqid_ds msd;
   11         if(msgctl(1,IPC_STAT,&msd) == -1){
   12                 perror("ipc stat msg error");
   13                 exit(-1);
   14         }
   15         printf("获取成功\n");
   16         return 0;
   17 }
  ```

  ###### 通过gdb调试获取的msd结构体内容：

  ```bash
  (gdb) display msd	#展示struct msqid_ds结构体属性
  
  1: msd = {msg_perm = {__key = 17119038, uid = 1000, gid = 1000, cuid = 1000, cgid = 1000, mode = 438, __seq = 0, __pad2 = 0, __glibc_reserved1 = 0,
      __glibc_reserved2 = 0}, msg_stime = 1791423541, msg_rtime = 1791423541, msg_ctime = 1791423425, __msg_cbytes = 0, msg_qnum = 0, msg_qbytes = 16384,
    msg_lspid = 135642, msg_lrpid = 135645, __glibc_reserved4 = 0, __glibc_reserved5 = 0}
  
  ```

  ###### MSG_INFO:获取内核针对消息队列的属性

  ```c
    1 #include <unistd.h>
    2 #include <sys/types.h>
    3 #include <sys/ipc.h>
    4 #include <sys/msg.h>
    5 #include <stdio.h>
    6 #include <stdlib.h>
    7 #include <string.h>
    8 //msgctl()获取消息队列的属性MSG_INFO
    9 int main(){
   10         struct msginfo info;	//返回的结构体是msginfo，传参时需要强转。
   11         if(msgctl(1,MSG_INFO,(struct msqid_ds*)&info) == -1){
   12                 perror("ipc stat msg error");
   13                 exit(-1);
   14         }
   15         printf("获取成功\n");
   16         return 0;
   17 }
  ```

  ###### gdb调试结果:

  ```bash
  (gdb) display info
  
  1: info = {msgpool = 1, msgmap = 0, msgmax = 8192, msgmnb = 16384, msgmni = 32000, msgssz = 16, msgtql = 0, msgseg = 65535}
  ```

  
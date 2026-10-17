#### 有名管道：

- #### 不局限于进程之间有共同祖先，使用文件名对管道进行持久化，当使用管道时，OS会在内存中找到一块合适的区域，作为管道存放数据的载体。正由于Linux宗旨一切皆文件，管道也可以通过文件方式进行操作：open、read、write、close等等

- #### 创建管道：

  ```c
  #include <sys/types.h>
  #include <sys/stat.h>
  /**
  	pathname: 管道名称
  	mode: 设定管道的权限，参考open()的第三个参数mode
  	return：
  		0 ： 创建成功
  		-1： 创建失败，errno存放错误码
  */
  int mkfifo(const char *pathname, mode_t mode);
  ```

  ###### 示例：

  ```c
    1 #include <unistd.h>
    2 #include <stdio.h>
    3 #include <stdlib.h>
    4 #include <sys/types.h>
    5 #include <sys/stat.h>
    6 #include <fcntl.h>
    7 //创建有名管道fifo
    8 int main(){
    9         char *path = "./myfifo";
   10         struct stat st;
   11         //判断管道是否已经命名
   12         if(stat(path,&st) == 0){
   13                 if(!S_ISFIFO(st.st_mode)){	//判断重名的文件是否为管道，不是管道返回错误
   14                         fprintf(stderr,"该文件不是管道文件，请重命名!\n");
   15                         exit(-1);
   16                 }
   17         }
   18         //如果管道还不存在，创建管道
   19         else if(mkfifo(path,0666) == -1){	//不要使用mkfifo()的EEXIST宏来判断管道文件是否存在
   20                 perror("mkfifo error");		//当同名文件不是管道文件时也会出现EEXIST错误
   21                 exit(-1);
   22         }
   23         pid_t pid;
   24         int fd;
   25         if((pid = fork()) == -1){
   26                 perror("fork error");
   27                 exit(-1);
   28         }
   29         if(pid ==0){
   30                 //打开管道.子进程以写入方式打开
   31                 fd = open(path,O_WRONLY);
   32                 if(fd == -1){
   33                         perror("open fifo error");
   34                         exit(-1);
   35                 }
   36                 char buf[128]= "hello world!";
   37                 write(fd,buf,sizeof(buf));
   38         }else{
   39                 fd = open(path,O_RDONLY);
   40                 if(fd == -1){
   41                         perror("open fifo error");
   42                         return -1;
   43                 }
   44                 char buf[128];
   45                 read(fd,buf,sizeof(buf));
   46                 fprintf(stdout,"%s\n",buf);
   47         }
   48         close(fd);
   49         return 0;
   50 }
  ```

  

- #### 有名管道当阻塞方式+(只读、只写)打开时，open函数会阻塞直到其他进程通过另一种方式(前者只读后者只写，或者前者只写后者只读)打开，open阻塞才会消失。

  #### 除此之外，当使用阻塞方式打开管道时，read、write系统调用均会阻塞，直到有数据读或写。

  ```c
    1 #include <stdio.h>
    2 #include <unistd.h>
    3 #include <stdlib.h>
    4 #include <sys/stat.h>
    5 #include <fcntl.h>
    6 //验证以只读方式、阻塞形式打开管道时，会阻塞到其他进程写打开后才会打开管道
        //该程序启动后会一直阻塞直到另一进程通过写方式打开
    7 int main(){
    8         mkfifo("./myfifo1",0666);
    9         int fd = open("./myfifo1",O_RDONLY);
   10         if(fd == -1)
   11                 perror("open fifo error");
   12         printf("管道打开成功, fd = %d\n",fd);
   13         return 0;
   14 }
  ```

  

- #### 管道打开的4种方式：

  ###### 前两种方式上面介绍过，即阻塞模式下的只读、只写方式。

  ###### 剩余的2中常用方式为非阻塞的只读、只写。

  ###### 为什么不使用读写模式打开？因为如果一个进程使用读写模式打开，该进程写入管道内的数据会被自己读到，读到的数据会被覆盖，导致其他进程会读不到完整数据，降低了进程间通信的可靠性。

  ```c
  /************带阻塞的管道操作，都会等到其他进程以另外一种方式打开管道后才会停止阻塞********************/
  //1、只读方式打开管道 myfifo
  int fd = open("./myfifo",O_RDONLY);
  //2、只写方式打开管道
  int fd = open("./myfifo",O_WRONLY);
  /************非阻塞的打开方式，只读模式与只写模式有所不同*******************************************/
  //3、只读方式打开，open成功并立即返回，即使没有进程以写方式打开。
  int fd = open("./myfifo",O_RDONLY | O_NONBLOCK);
  //4、只写方式打开。如果已经有其他进程以只读方式打开，open调用成功并返回。
  //但是，如果没有进程以读模式打开管道，open将调用失败，返回-1.目的就是为了防止非阻塞模式下持续写不读取导致内存溢出。
  int fd = open("./myfifo",O_WRONLY | O_NONBLOCK);
  //没有进程以读方式打开管道时的输出：
  //open fifo error: No such device or address
  ```

  

- #### 管道如果全部关闭写端，阻塞的读端就不在阻塞，会持续从管道读取数据，读取完数据后仍旧持续读取0字节数据。当写进程再次开启，读进程又恢复到阻塞状态。

- #### 如果管道全部关闭读端，写端进程再次写入数据时会被OS发出SIGPIPE信号，之后会被强制杀死。

  ```c
    1 #include <stdio.h>
    2 #include <unistd.h>
    3 #include <stdlib.h>
    4 #include <sys/stat.h>
    5 #include <fcntl.h>
    6 #include <string.h>
    7 //读端进程。
    8 int main(){
    9         mkfifo("./myfifo1",0666);
   10         int fd = open("./myfifo1",O_RDONLY);
   11         if(fd == -1){
   12                 perror("open fifo error");
   13                 return -1;
   14         }
   15         printf("管道打开成功, fd = %d\n",fd);
   16         char buf[128];
   17         while(1){
   18                 bzero(buf,sizeof(buf));
   19                 read(fd,buf,sizeof(buf));	//如果写端关闭，读端的read不再阻塞，会持续读
   20                 fprintf(stdout,"[%s]\n",buf);
   21         }
   22         return 0;
   23 }
  ```

  ```c
    1 #include <stdio.h>
    2 #include <unistd.h>
    3 #include <stdlib.h>
    4 #include <sys/stat.h>
    5 #include <fcntl.h>
    6 //验证以只写方式、阻塞形式打开管道时，会阻塞到其他进程读打开后才会打开管道
    7 int main(){
    8         mkfifo("./myfifo1",0666);
    9         int fd = open("./myfifo1",O_WRONLY);
   10         if(fd == -1){
   11                 perror("open fifo error");
   12                 return -1;
   13         }
   14         printf("管道打开成功, fd = %d\n",fd);
   15         while(1){
   16                 write(fd,"hello world",12);	//写端2秒一次写入管道，当读端关闭后，写端再次写入数据时被杀死。
   17                 sleep(2);
   18         }
   19         return 0;
   20 }
  ```

  

- ###### 综合(使用2个管道实现2个会话之间通信)：chat.c

  ###### 注意：一定要在每个进程内部进行管道的打开，这样可避免死锁的产生。

  ###### 			假如在fork()之前打开这两个管道，要注意按照资源(也就是管道)的顺序打开，否则会产生死锁。

  ###### 			死锁的情况： 

  ###### 		session1打开顺序为myfifo1只读,myfifo2只写,阻塞方式打开，进程会阻塞在打开myfifo1等待myfifo1的只写端的开启。

  ###### 		session2打开myfifo2只读，myfifo1只写，进程会阻塞在myfifo2的open函数等待myfifo2的只写端打开，此时2个进程产生死锁。

  ```c
    1 #include <unistd.h>
    2 #include <stdio.h>
    3 #include <stdlib.h>
    4 #include <string.h>
    5 #include <sys/types.h>
    6 #include <sys/stat.h>
    7 #include <fcntl.h>
    8 #include <sys/wait.h>
    9 //定义需要开启的管道
   10 #define BUF_SIZE 256
   11 typedef struct {	//定义消息结构体，其中存放发送放的进程id与具体消息。
   12         pid_t pid;
   13         char buf[BUF_SIZE];
   14 } message_t;
   15 int main(int argc,char ** argv){
   16         if(argc < 3){	//使用传参形式传入读、写通道
   17                 fprintf(stderr,"参数必须要有读管道文件、写管道文件\n");
   18                 exit(-1);
   19         }
   20         //判断管道是否存在
   21         if(access(argv[1],F_OK) == -1 && mkfifo(argv[1],0644) == -1){
   22                 //创建管道
   23                 perror("mk fifo1 error");
   24                 exit(-1);
   25         }
   26         if(access(argv[2],F_OK) == -1 && mkfifo(argv[2],0644) == -1){
   27                 //创建管道
   28                 perror("mk fifo2 error");
   29                 exit(-1);
   30         }
   31         //打开文件描述符
   32         int r_fd= -1,w_fd = -1;
   33         ssize_t nbytes;
   34         message_t msg;
   35         //创建子进程，分别对管道进行读写
   36         pid_t pid;
   37         if((pid = fork()) == -1){
   38                 perror("fork error");
   39                 goto fail_ret;
   40         }
   41         //子进程负责读取管道
   42         if(pid == 0){
   43                 if((r_fd = open(argv[1],O_RDONLY)) == -1){	//argv[1]为读通道
   44                         perror("open fifo1 error");
   45                         goto fail_ret;
   46                 }
   47                 while(1){
   48                         nbytes = read(r_fd,&msg,sizeof(message_t));
   49                         if(nbytes == 0){
   50                                 printf("对方已关闭对话\n");
   51                                 break;
   52                         }
   53                         fprintf(stdout,"%d : %s\n",msg.pid,msg.buf);
   54                 }
   55                 close(r_fd);
   56                 unlink(argv[1]);
   57                 exit(0);
   58         }else{
   59                 if((w_fd = open(argv[2],O_WRONLY)) == -1){	//argv[2]为写通道
   60                         perror("open fifo2 error");
   61                         goto fail_ret;
   62                 }
   63                 //父进程负责写入管道
   64                 msg.pid = getpid();
   65                 while(1){
   66                         scanf("%s",msg.buf);
   67                         nbytes = write(w_fd,&msg,sizeof(message_t));
   68                         //完善还需要注册SIGCHLD信号的处理事件，以免默认SIGIGN被忽略。
   69                         printf("nbytes = %ld\n",nbytes);
   70                         /*
   71                         if(nbytes == -1){
   72                                 perror("write error");
   73                                 waitpid(pid,NULL,0);
   74                                 break;
   75                         }
   76                         */
   77                 }
   78         }
   79         close(w_fd);
   80         unlink(argv[2]);
   81         return 0;
   82 fail_ret:
   83         if(r_fd != -1){
   84                 close(r_fd);
   85                 unlink(argv[1]);
   86         }
   87         if(w_fd != -1){
   88                 close(w_fd);
   89                 unlink(argv[2]);
   90         }
   91         exit(-1);
   92 }
  ```

  ###### 开启2个会话的指令分别为：

  ```bash
  #管道为半双工通信，所以需要使用2个管道。2个会话分别连接同2个管道，每个会话有2个进程，每个进程分别开启一个管道的读、写端
  ./chat ./myfifo1 ./myfifo2	#开启第一个会话，该会话的读端为管道myfifo1，写端为myfifo2
  ./chat ./myfifo2 ./myfifo1	#开启第二个会话，读端为myfifo2，写端为myfifo1
  ```

  
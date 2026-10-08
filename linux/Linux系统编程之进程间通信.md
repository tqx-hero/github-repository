# Linux系统编程之进程间通信

1. ### 无名管道：

   - ##### 通过pipe读取(man 3 pipe)：

   ###### 一段共享的内存区域，一端用来写入数据，一端用来读取数据。

   ###### 不同进程要想共享这个内存区域，必须使用相同的写入端与读取端，那就是需要拥有相同的文件描述符。因此各个进程之间必须是经过同一个进程fork一次或者多次生成的。

   ```c
   #include <unistd.h>
   /**
   	files: 传入大小为2的整型数组，返回读写的2个文件描述符。
   		files[0] : 读取端的文件描述符
   		files[1] : 写入端的文件描述符
   	return：
   		0： 管道创建创建成功
   		-1: 创建失败，错误码errno
   */
   int pipe(int fildes[2]);
   int close(int fd);
   ```

   ###### demo(创建管道，并fork出子进程，子进程负责读取管道数据，父进程写入管道数据):

   ```c
     1 #include <stdio.h>
     2 #include <unistd.h>
     3 #include <stdlib.h>
     4 #include <string.h>
     5
     6 int main(){
     7         int fds[2];
     8         ssize_t nbytes;
     9         //创建管道，生成读写2端的文件描述符
    10         if(pipe(fds) == -1){
    11                 perror("pipe create error");
    12                 exit(-1);
    13         }
    14         switch(fork()){
    15                 case -1:
    16                         perror("fork error");
    17                         break;
    18                 case 0:
    19                         //子进程，仅读取管道内的数据
    20                         close(fds[1]);  //关闭写管道，因为只用读取
    21                         char buf[128];
    22                         nbytes = read(fds[0],buf,sizeof(buf));
    23                         fprintf(stdout,"读到的管道内容：%s\n",buf);
    24                         close(fds[0]);
    25                         break;
    26                 default:
    27                         //父进程，只写入管道
    28                         close(fds[0]);
    29                         char* rstr = "国庆快乐，同志们!";
    30                         write(fds[1],rstr,strlen(rstr)+1);
    31                         close(fds[1]);
    32                         break;
    33         }
    34         return 0;
    35 }
   ```

   - ##### 通过popen读取(man 3 popen)：

     ###### popen()可以通过命令行、可执行脚本为输入端或输出端，对其进行读取、写入。

     ```c
     #include <stdio.h>
     /**
     	开启管道，连接命令行与FILE句柄
     	command: 
     		管道一端的命令或者可执行程序
     	type:
     		"r": 以读方式从command读取数据到FILE*
     		"w": 以写方式从FILE*向command写入数据
     */
     FILE *popen(const char *command, const char *type);
     //关闭管道
     int pclose(FILE *stream);
     ```

     ###### 以r方式打开管道（等价于：uname -a | more）：

     ```c
       1 #include <unistd.h>
       2 #include <stdio.h>
       3 //#include <unistd.h>
       4 //popen()函数的r使用
       5 int main(){
       6         FILE* fptr = popen("uname -a","r"); //以读取的方式打开一个管道，该管道从第一个参数(命令)中读取
       7         char buf[128];
       8         if(fptr){
       9                 fread(buf,1,sizeof(buf),fptr); //读取管道内的数据
      10                 fprintf(stdout,"%s\n",buf);
      11         }
      12         pclose(fptr);
      13         return 0;
      14 }
     ```

     ###### 输出：

     ```bash
     tqx@linux-ubuntu$ ./popen
     Linux linux-ubuntu.org 5.15.0-139-generic #149~20.04.1-Ubuntu SMP Wed Apr 16 08:29:56 UTC 2025 x86_64 x86_64 x86_64 GNU/Linux
     ```

   

   ###### 		以w方式打开管道（等价于： echo "国庆节快乐，同志们!" | more ）：

   ​		

   ```c
     1 #include <stdio.h>
     2 #include <unistd.h>
     3 //popen()以w方式打开管道
     4 int main(){
     5         FILE* wptr = popen("more","w");	//以写入方式打开管道，FILE*作为命令more的输入端
     6         if(!wptr){
     7                 perror("popen pipe error");
     8                 return -1;
     9         }
    10         char buf[]="国庆节快乐，同志们!";
    11         fwrite(buf,1,sizeof(buf),wptr); //将信息写入管道
    12         pclose(wptr);
    13         return 0;
    14 }
   ```

   ###### 多次读取：

   ```c
     1 #include <stdio.h>
     2 #include <string.h>
     3 #include <stdlib.h>
     4 #define BUFSIZE 1023
     5 //读取ps -aux并输出
     6 int main(){
     7         FILE* rptr = popen("ps -aux","r");
     8         if(!rptr){
     9                 perror("popen ps -aux error");
    10                 return -1;
    11         }
    12         //读取管道内的数据
    13         char buf[BUFSIZE+1];
    14         ssize_t nbytes;
    15         while(1){
    16                 nbytes = fread(buf,sizeof(char),BUFSIZE,rptr);
    17                 buf[nbytes]=0;
    18                 fprintf(stdout,"%s",buf);
    19                 if(nbytes < BUFSIZE)
    20                         break;
    21         }
    22         fclose(rptr);
    23         return 0;
    24 }
   ```

   

   - ###### pipe()+fork()+exec()实现父进程往管道内写入数据，子进程从管道内读取数据：

     ###### pipe2.c:

     ```c
       //pipe2.c: 创建管道、fork子进程，子进程execv执行另一个程序(通过argv传递管道的fd),父进程写入数据，最后waitpid回收子进程.
       1 #include <stdio.h>
       2 #include <unistd.h>
       3 #include <stdlib.h>
       4 #include <sys/wait.h>
       5 //使用pipe()+fork()+exec()实现跨进程之间的管道通信
       6 //父进程负责往管道内写入，子进程负责读取出来
       7 int main(){
       8         //pipe创建管道
       9         int filedes[2];
      10         pid_t pid;
      11         if(pipe(filedes) == -1){
      12                 perror("create pipe error");
      13                 exit(-1);
      14         }
      15         //创建子进程
      16         if((pid = fork()) == -1){
      17                 perror("fork error");
      18                 close(filedes[0]);
      19                 close(filedes[1]);
      20                 exit(-1);
      21         }
      22         if(pid == 0){
      23                 //子进程去执行另一个程序
      24                 char rfd[16],wfd[16];
          				//将读写管道的fd打包成字符串格式，放入argv数组作为exec()的参数
      25                 sprintf(rfd,"%d",filedes[0]);
      26                 sprintf(wfd,"%d",filedes[1]);
      27                 char * argv[] = {"pipe3",rfd,wfd,NULL};
      28                 execv("./pipe3",argv);	//子进程执行同目录下的pipe3程序
      29                 perror("execv pipe3 error");
      30                 exit(-1);
      31         }
      32         //父进程负责写入数据
      33         char buf[] = "大家好才是真的好!";
      34         write(filedes[1],buf,sizeof(buf));
      35         close(filedes[0]);
      36         close(filedes[1]);
      37         //父进程等待子进程结束，回收PCB
      38         waitpid(pid,NULL,0);
      39         return 0;
      40 }
     ```

     ###### pipe3.c(子进程exec执行的程序，读取父进程写入管道内的消息):

     ```c
       1 #include <stdio.h>
       2 #include <string.h>
       3 #include <stdlib.h>
       4 #include <unistd.h>
       5 //pipe2子进程执行的程序，用于输出父进程写入管道的内容
       6 int main(int argc,char** argv){
       7         int rfd,wfd;
       8         sscanf(argv[1],"%d",&rfd);	//格式化读写fd，还原成int类型
       9         sscanf(argv[2],"%d",&wfd);
      10         printf("rfd = %d\n",rfd);
      11         printf("wfd = %d\n",wfd);
      12         close(wfd); //关闭写描述符
      13         char buf[128];
      14         read(rfd,buf,sizeof(buf));	//通过fd读取管道的消息
      15         printf("管道中的内容：%s\n",buf);
      16         close(rfd);
      17         return 0;
      18 }
     ```

   - ###### 也可以使用fcntl系统调用设置文件描述符的属性，例设置读fd为非阻塞：

     ```c
     #include <stdio.h>
       2 #include <unistd.h>
       3 #include <fcntl.h>
       4 #include <stdlib.h>
       5 #include <errno.h>
       6 int main(){
       7         int filedes[2];
       8         if(pipe(filedes) == -1){
       9                 perror("create pipe error");
      10                 exit(-1);
      11         }
      12         pid_t pid;
      13         char buf[128];
      14         if((pid = fork()) == -1){
      15                 perror("fork error");
      16                 exit(-1);
      17         }else if(pid ==0){
      18                 //子进程的处理
      19                 close(filedes[1]);      //子进程只负责读，关闭写
      20                 //循环读，设置描述符为非阻塞状态
      21                 int flag = fcntl(filedes[0],F_GETFL);
      22                 flag |= O_NONBLOCK;
      23                 fcntl(filedes[0],F_SETFL,flag);
      24                 ssize_t nbytes;
      25                 while(1){
      26                         nbytes = read(filedes[0],buf,sizeof(buf));
      27                         if(nbytes == -1 &&  errno == EAGAIN){
      28                                 //printf("未读到消息..\n");
      29                                 continue;
      30                         }
      31                         if (nbytes == -1){
      32                                 perror("read fd error");
      33                                 close(filedes[0]);
      34                                 exit(-1);
      35                         }
      36                         if(!nbytes){
      37                                 fprintf(stdout,"读取结束\n");
      38                                 close(filedes[0]);
      39                                 exit(0);
      40                         }
      41                         fprintf(stdout,"%s\n",buf);
      42                 }
      43         }else{
      44                 close(filedes[0]);
      45                 int i=0;
      46                 while(1){
      47                         char message[] = "hello world!";
      48                         write(filedes[1],message,sizeof(message));
      49                         sleep(1);
      50                 }
      51         }
      52
      53         return 0;
      54 }
     ```

     

   - ###### 当管道的读端全部关闭后，如果还有进程往这个管道写入数据，OS会给该进程发送SIGPIPE（管道破裂信号）,并杀死该进程:

     ```c
      1 #include <stdio.h>
       2 #include <string.h>
       3 #include <unistd.h>
       4 #include <sys/wait.h>
       4 //测试sigpipe信号
       5 int main(){
       6         int fds[2];
       7         pid_t pid;
       8         if(pipe(fds) == -1){
       9                 perror("pipe error");
      10                 return -1;
      11         }
      12         if((pid = fork()) == -1){
      13                 perror("fork error");
      14                 close(fds[0]);
      15                 close(fds[1]);
      16                 return -1;
      17         }
      18         if(pid ==0){
      19                 char buf[1024];
      20                 close(fds[0]);	//子进程关闭读fd
      21                 printf("子进程中...\n");
      22                 memset(buf,'a',sizeof(buf));
      23                 int i=1;
      24                 ssize_t nbytes;
      25                 while(1){
      26                         sleep(2);
          						//由于没有进程开启管道的读fd，该进程会收到SIGPIPE信号并被杀死
      27                         nbytes = write(fds[1],buf,sizeof(buf));
      28                         if(nbytes == -1){
      29                                 perror("write error");
      30                                 break;
      31                         }
      32                         printf("i = %d\n",i++);
      33                 }
      34         }
      35         else{
      36                 close(fds[0]);	//父进程关闭读fd
      37                 waitpid(-1,NULL,0);	//父进程等待子进程结束回收PCB
      38         }
      39 //      close(fds[0]);
      40         close(fds[1]);
      41         return 0;
      42 }
     ```

     

   - 

2. ### 有名管道：

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

     

   - 

3. ### 消息队列：

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

     

   - 

4. ### mmap：

5. ### 共享内存：

6. 
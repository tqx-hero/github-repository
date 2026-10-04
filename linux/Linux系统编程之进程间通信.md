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
     //但是，如果没有进程以读模式打开管道，open将调用失败，返回-1.
     int fd = open("./myfifo",O_WRONLY | O_NONBLOCK);
     //没有进程以读方式打开管道时的输出：
     //open fifo error: No such device or address
     ```

     

   - 

3. ### 消息队列：

4. ### mmap：

5. ### 共享内存：

6. ## 
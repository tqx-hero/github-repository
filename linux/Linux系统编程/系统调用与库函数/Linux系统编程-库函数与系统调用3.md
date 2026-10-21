### Linux系统编程-库函数与系统调用3：

- #### 重定向对标准输入、输出的影响：

  以输出重定向 `>` 为例,启动程序：

  ```shell
  $ ./menu > file
  ```

  上述程序会将程序中使用标准输出原本打印到终端的文本全部重定向输出到文件file中，原理就是：

  > 前置知识：
  >
  > 标准输入和输出是对终端的读与写的2个过程。在Linux中一切皆文件，终端也抽象成了一个文件:`/dev/tty`。
  >
  > 标准输入就是以只读方式打开了这个文件：
  >
  > ​	int in = open("/dev/tty",O_RDONLY);
  >
  > 标准输出就是只写方式打开了它：
  >
  > ​	int out = open("/dev/tty",O_WRONLY);

  > 1、在执行这个程序之前，当前终端，也就是shell进程使用系统调用open先把使用到的文件`file`，获得它的文件描述符fd，如：
  >
  > ​	int fd = open("file",O_CREAT | O_WRONLY,0664)。
  >
  > ​	打开的操作背后是：
  >
  > ​	内核会在全局文件打开表中新增一个文件表项，把表项在数组的下标复制到进程的文件描述符表中；
  >
  > ​	文件描述符表也可以看成是一个数组，添加这一项之后，系统调用open函数会返回这一项在数组中的偏移量，即下标，这就是文件描述符fd。
  >
  > 2、fork()创建子进程，该函数会复制父进程打开的文件描述符，同时内核会修改fd指向的文件打开表项，将它的打开记录+1。这样就实现了父子进程共享这个文件表项的所有信息，包括读写指针。
  >
  > 3、子进程调用dup2(fd,1)，将1指向的文件表项删除，也就是关闭标准输出；将fd指向的文件表项复制给标准输出的描述符1，close(fd)，关闭fd的引用。这样就将文件描述符1重定向到了文件file。
  >
  > 4、当库函数printf、fprintf(stdout)进行输出内容时，底层调用的都是write(1)，往文件描述符`1`中写数据，而子进程当前的文件描述符`1`指向的文件实际上不是`/dev/tty`文件，而是file文件，调用`write(1)`就会写入file文件。

  ##### demo1：

  源代码`menu1.c`编译后得到`menu`:

  ```c
  #include <stdio.h>
  #include <stdlib.h>
  
  char* menu[] ={
          "a - add new record",
          "d - delete a record",
          "q - quit",
          NULL
  };
  //选择界面
  int getChose(char* info,char** menu){
          int selected,chosed;
          //加载界面
          char** ops = menu;
          while(*ops)
                  printf("%s\n",*ops++);
          printf("%s\n",info);
          selected = getchar();
          while(getchar() != '\n');//读取剩余字符直到读到\n
          ops = menu;
          chosed = 0;
          while(*ops){
                  if(selected == (*ops)[0]){
                          chosed =1;
                          break;
                  }
                  ops++;
          }
          //如果选择的不对，则进行选择
          if(!chosed){
                  printf("输入有误，请重新选择!\n");
                  return getChose(info,menu);
          }
          return selected;
  }
  
  int main(){
          int chose;
          do{
                  chose = getChose("请选择对菜单的操作:",menu);
                  printf("你选择的操作是: %c\n",chose);
          }while(chose != 'q');
          return 0;
  }
  ```

  当对程序进行重定向后：

  ```bash
  $./menu > file.txt
  ```

  所有printf输出的消息都放在了`file.txt`文件中。

  ##### demo2：

  `menu2.c` 使用打开文件流的方式`fopen("/dev/tty")`打开标准输入输出文件流，实现了对该文件的直接操作:

  ```c
  #include <stdio.h>
  #include <stdlib.h>
  #include <unistd.h>
  #define FILE_NAME "/dev/tty"
  char* menu[] ={
          "a - add new record",
          "d - delete a record",
          "q - quit",
          NULL
  };
  //选择界面
  int getChose(char* info,char** menu,FILE* in,FILE* out){
          int selected,chosed;
          //加载界面
          char** ops = menu;
          while(*ops)
                  fprintf(out,"%s\n",*ops++);
          fprintf(out,"%s\n",info);
          selected = getc(in);
          while(getc(in) != '\n');//读取剩余字符直到读到\n
          ops = menu;
          chosed = 0;
          while(*ops){
                  if(selected == (*ops)[0]){
                          chosed =1;
                          break;
                  }
                  ops++;
          }
          //如果选择的不对，则进行选择
          if(!chosed){
                  fprintf(stderr,"输入有误，请重新选择!\n");
                  return getChose(info,menu,in,out);
          }
          return selected;
  }
  
  int main(){
          int chose;
          FILE *in,*out;
          //判断标准输出的fd是否连接到终端
          if(!isatty(fileno(stdout)))
                  fprintf(stderr,"标准输出已重定向!\n");
          //使用打开文件流的方式获取文件输入输出流
          in = fopen(FILE_NAME,"r");
          out = fopen(FILE_NAME,"w");
          do{
                  chose = getChose("请选择对菜单的操作:",menu,in,out);
                  fprintf(out,"你选择的操作是: %c\n",chose);
          }while(chose != 'q');
          return 0;
  }
  ```

  

  其中用到了两个函数：

  ```c
  #include <stdio.h>
  //通过文件流获得它的文件描述符
  int fileno(FILE *stream);
  
  //另一个fd与文件流关联函数,将fd关联到文件流并返回。
  FILE *fdopen(int fd, const char *mode);
  
  #include <unistd.h>
  //文件描述符fd是否指向终端：1、是；0：不是
  int isatty(int fd);
  ```

  使用命令：

  ```bash
  $./menu2 > file.txt 
  ```

  该文件中的所有输出都在终端正常显示，不受重定向的影响了，说明直接打开`/dev/tty`文件对其进行读写等同于对终端进行读写，验证了上面的观点。

- 
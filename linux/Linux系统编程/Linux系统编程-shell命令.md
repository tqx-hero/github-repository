1. 查看当前内存使用情况：

   ```shell
   free -h
   ```

   

2. 查看当前正在连接的用户：

   ```shell
   who
   ```

   

3. 查看当前服务器的运行模式：

   ```shell
   runlevel 
   #输出格式为：上一次运行模式  当前运行模式
   #运行模式：
   -3： 命令行
   -5： 图形界面
   ```

   ![image-20260905153639054](C:\Users\田庆新\AppData\Roaming\Typora\typora-user-images\image-20260905153639054.png)

4. 切换运行模式到命令行：

   ```shell
   init 3
   #切换到图形
   init 5
   ```

   

5. 修改主机名：

   ```shell
   #主机名不要有_
   hostnamectl set-hostname 主机名
   ```

   

6. 显示当前用户：

   ```shell
   whoami
   ```

   

7. 切换到root用户：

   ```shell
   sudo -i
   #输入非root的密码，exit退出root用户
   ```

   

8. 设置服务器时间、时区：

   ```shell
   timedatectl set-timezone Asia/Shanghai
   #可用list-timezones列出所有支持的时区
   timedatectl list-timezones
   #查看当前的时区：
   ll /etc/localtime
   ```

   ![image-20260907170604978](C:\Users\田庆新\AppData\Roaming\Typora\typora-user-images\image-20260907170604978.png)

9. 查看某个命令的类型(vim/echo等)：

   ```shell
   #查询到第一个就返回显示
   type vim [echo]
   #显示所有的echo命令
   type -a echo
   ```

   

10. 查看已经缓存到内存的命令：

    ```shell
    hash
    ```

    ![image-20260905164905028](C:\Users\田庆新\AppData\Roaming\Typora\typora-user-images\image-20260905164905028.png)

11. 使新增的配置生效：

    ```shell
    source abc.sh
    #或者使用 . ，与source效果相同
    . abc.sh
    ```

    

12. 使能、禁用echo命令：

    ```shell
    #启用
    enable [op] echo
    #禁用
    enable -n echo
    ```

    

13. 显示外部命令的位置：

    ```shell
    #显示外部命令的位置
    which echo
    #显示外部命令与帮助文档的位置
    whereis echo
    ```

    ![image-20260905171930458](C:\Users\田庆新\AppData\Roaming\Typora\typora-user-images\image-20260905171930458.png)

14. 对命令缓存的处理：

    ```shell
    #显示所有缓存的命令
    hash
    #删除名称是which的命令
    hash -d which
    #删除所有缓存的命令
    hash -r
    ```

    

15. 给指令起别名：

    ```shell
    #临时：给指令：cd /home/tqx/net起一个别名叫cps
    #注意:别名的优先级非常高，如果别名与已有指令名相同会覆盖它，所以别名必须不能与已有指令相同，以免产生歧义
    alias cps="cd /home/tqx/net"
    #全局生效,写入配置文件.bashrc
    cd ~ && vim .bashrc
    #在最后添加上这条别名规则
    alias cps="cd /home/tqx/net"
    #使配置文件生效
    source(.也可以) .bashrc
    ```

    ![image-20260905173438461](C:\Users\田庆新\AppData\Roaming\Typora\typora-user-images\image-20260905173438461.png)

16. 查看当前环境下已有的别名指令：

    ```shell
    alias [-p]
    #临时取消别名
    unalias NAME
    #永久取消需要删除配置文件中的相关项
    ```

    

17. 查看当前机器的硬盘使用情况：

    ```shell
    lsblk
    ```

    

18. 查看CPU的详细信息：

    ```shell
    lscpu
    #或者直接到/proc/目录下打开相关文件查找(proc不是具体的磁盘上的文件，而是一块存储各种信息的内存)
    cat /proc/cpuinfo
    ```

    

19. 查看内核版本：

    ```shell
    uname -r
    ```

    ![image-20260907163111901](C:\Users\田庆新\AppData\Roaming\Typora\typora-user-images\image-20260907163111901.png)

20. 查看操作系统的信息：

    ```shell
    #centos:
    cat /etc/redhat-release
    cat /etc/os-release
    #ubuntu:
    cat /etc/os-release
    ```

    ![image-20260907163541479](C:\Users\田庆新\AppData\Roaming\Typora\typora-user-images\image-20260907163541479.png)

    ![image-20260907163636220](C:\Users\田庆新\AppData\Roaming\Typora\typora-user-images\image-20260907163636220.png)

21. 显示日历：

    ```shell
    cal
    ```

    ![image-20260907171100128](C:\Users\田庆新\AppData\Roaming\Typora\typora-user-images\image-20260907171100128.png)

22. 多长时间后关机：

    ```shell
    #十分钟后关机
    shutdown +10
    #设置15:20分关机
    shutdown 15:20
    #取消关机的操作
    shutdown -c
    ```

    ![image-20260908143854085](C:\Users\田庆新\AppData\Roaming\Typora\typora-user-images\image-20260908143854085.png)

23. 查看当前登录的用户：

    ```shell
    w
    ```

    ![image-20260908144151806](C:\Users\田庆新\AppData\Roaming\Typora\typora-user-images\image-20260908144151806.png)

24. 安装会话管理软件：

    ```shell
    #screen 可以管理session，创建回话后开启新的进程去处理一些长时间的任务，在终端异常断开时也能在后台继续执行
    sudo apt install screen
    #打开新的回话
    screen
    ```

    ![image-20260908145802980](C:\Users\田庆新\AppData\Roaming\Typora\typora-user-images\image-20260908145802980.png)

25. screen屏幕同步(会话协同)：

    ```shell
    #展示所有screen会话
    screen -ls(或者-list)
    #创建socket名称为tqx的screen会话
    screen -S tqx
    #另一个shell进程加入tqx会话
    screen -x tqx
    #恢复某sesstin会话,会话必须是detach状态的，session选项可以是pid，或者名称
    screen -r [session]
    #退出当前screen会话
    ctrl a+d
    #退出并关闭screen
    exit
    ```

    

26. 增强版screen----tmux：

    ```shell
    #安装(centos)
    yum install tmux
    #ubuntu
    sudo apt install tmux
    #分屏：上下分屏(注意：ctrl+b一起按，"格外按)
    ctrl+b "
    #左右分屏(按键规则同上)：
    ctrl+b %
    #光标切换
    ctrl+b 方向键
    #列出所有tmux的快捷键
    tmux list-keys
    #列出所有命令：
    tmux list-command
    #关闭窗口：
    exit
    ```

    

27. echo:

    ```shell
    #输出字符串，也可以取变量的内容输出(字符串形式)
    echo [-ne] [options]
    -n:输出时不换行输出。默认为换行输出
    -e：启用字符解释功能，如:echo -e "\a"指令不会输出字符串a,会将其解释成\a功能，即发出警告声音
    #输出八进制数\0127的字符表示W
    echo -e "\0127"
    #输出十六进制数0x61的字符表示a
    echo -e "\x61"
    选项：
    -str：可以是任意字符串，如果中途有空格，需要使用""或者''括起来
    -$param：param表示变量名，使用$进行获取指定变量的字符串值
    
    ```

    ![image-20260908171647572](C:\Users\田庆新\AppData\Roaming\Typora\typora-user-images\image-20260908171647572.png)

28. 显示当前字符集：

    ```shell
    echo $LANG
    #字符集的配置文件在/etc目录下
    #centOS：/etc/locale.conf
    #ubuntu:/etc/default/grub
    ```

    

    

29. 以十六进制数显示某个文本：

    ```shell
    hexdump -C text.txt
    ```

    ![image-20260908165445688](C:\Users\田庆新\AppData\Roaming\Typora\typora-user-images\image-20260908165445688.png)

30. echo中单引号与双引号：

    ```shell
    echo "$PATH" #双引号为弱引用，echo解析时会将变量进行替换，而不是按照字符串解释
    echo '$PATH' #单引号为强引用，在引号内的全部解析成字符串.
    ```

    

31. 反向单引号：

    ```shell
    #注意，以下所有指令都是需要双引号括起来，如果换成单引号会输出原字符串内容，不会进行任何解释
    echo "local host is `hostname`" #会将反向单引号中的内容当成指令解读，效果同$(hostname)相同
    echo "local host is $(hostname)" #该写法与上述等价
    echo "local host is $hostname" #不加()的$是取变量的内容
    ```

    

32. 输出当前日期：

    ```shell
    date +%F
    #常用日志备份指令
    touch `date +%F`.log	#创建一个日志文件，以今日年月日作为文件名
    touch $(date +%F).log	#与上述命令等价
    touch `hostname`-$(date +%F).log	#或者可以与其他指令拼接起来使用
    ```

    ![image-20260909172134144](C:\Users\田庆新\AppData\Roaming\Typora\typora-user-images\image-20260909172134144.png)

    ![image-20260909172240022](C:\Users\田庆新\AppData\Roaming\Typora\typora-user-images\image-20260909172240022.png)

33. 花括号使用：

    ```shell
    echo file{11,22,33}	#表示输出以file为前缀的三个字符串：file11,file22,file33
    echo {1..10}	#输出[1,10]范围内的所有数,支持降序如：{100..10}
    echo {a..z}		#输出字母a-z,支持降序如：{m..a}
    echo {100..200..2}	#输出连续区间[100,200]之间的数，每个数的间隔为2，结果就是取的所有[100,200]之间的偶数
    ```

    ![image-20260909180746007](C:\Users\田庆新\AppData\Roaming\Typora\typora-user-images\image-20260909180746007.png)

    ![image-20260909180846188](C:\Users\田庆新\AppData\Roaming\Typora\typora-user-images\image-20260909180846188.png)

34. 查看键入的命令历史记录：

    ```shell
    history
    #在文件~/.bash_history,当进程结束时，系统会把新敲的命令追加到该文件后面
    history [-c] [-d offset] [n]
    -c:	清空历史记录。注意清空的是内存中的记录，而不会直接清空文件
    -d offset: 删除某一项，offset为序号
    n:	仅展示最后的n项
    #重新执行第2011条指令(在history中记录的第2011条指令)
    !2011
    #执行倒数第2条指令
    !-2
    ```

    ![image-20260910132220753](C:\Users\田庆新\AppData\Roaming\Typora\typora-user-images\image-20260910132220753.png)

    ![image-20260910133140773](C:\Users\田庆新\AppData\Roaming\Typora\typora-user-images\image-20260910133140773.png)

35. shell快捷键：

    ```shell
    ctrl + s	#锁屏幕，不再显示输入信息，但是指令还是会执行
    ctrl + q	#解除锁屏幕状态
    ctrl + u	#删除光标前面的所有信息
    ctrl + k	#删除光标后面的所有信息
    alt + r 	#删除整行，必须是手动键入的才行 
    ```

    

36. 大体了解指令的作用：

    ```shell
    whatis rm 	#打印出rm命令的作用
    man -f rm	#与上述指令等价
    ```

    

37. 生成man文档：

    ```shell
    mandb
    ```

    

38. 显示日期：

    ```shell
    date +%F%T	#显示日期+时间
    %T:	相当于%H:%M:%S
    #生成日期+时间命名的日志文件：
    touch `date +"%F-%H_%M_%S"`.log
    ```

    ![image-20260910171428882](C:\Users\田庆新\AppData\Roaming\Typora\typora-user-images\image-20260910171428882.png)

39. 查看环境变量，以及设置的变量值：

    ```shell
    env		#查看环境变量
    export -p #查看所有变量值
    export command="ls && cat file" #设置环境变量的变量值command,可以使用export -p 查看到
    ```

    ![image-20260910215219358](C:\Users\田庆新\AppData\Roaming\Typora\typora-user-images\image-20260910215219358.png)

    ![image-20260910215233396](C:\Users\田庆新\AppData\Roaming\Typora\typora-user-images\image-20260910215233396.png)

40. 分别执行多条指令：

    ```shell
    #指令可以有多条，指令之间用;隔开
    eval ls ./;hostname	#分别执行查看当前目录下的文件、查看当前用户名这两条指令
    ```

    ![image-20260910220844492](C:\Users\田庆新\AppData\Roaming\Typora\typora-user-images\image-20260910220844492.png)

41. 显示文件的内容：

    ```shell
    #显示文件的内容,同时显示行号
    nl file
    #显示文件的信息
    wc [-clw][--help][--version][file...]
    -c: --bytes/--chars,只显示字节数
    -l: --lines显示行数
    -w: --words显示字数
    --help: 帮助文档
    --version: 版本
    ```

    ![image-20260910221643993](C:\Users\田庆新\AppData\Roaming\Typora\typora-user-images\image-20260910221643993.png)

    ![image-20260910224102412](C:\Users\田庆新\AppData\Roaming\Typora\typora-user-images\image-20260910224102412.png)

42. 修改文件内容：

    ```shell
    #Linux sed 命令
    #可依照脚本的指令来处理、编辑文本文件,只是进行处理工作，如果持久化就需要重定向
    sed [-hnV][-e<script>][-f<script文件>][文本文件file]
    ```

    **Option：**

    - -h: --help
    - -n: --quiet或--silent 仅显示script处理后的结果。
    - -V: --version
    - -e<script>: --expression=<scrpit>,以选中的script脚本来处理输入的文本文件file
    - -f<script文件>: --file=<script文件>，以选中的script文件来处理输入的文本文件file

    **动作说明：**

    - a:新增，a的后面接字符串，字符串可以在当前行的下一行出现。
    - c:取代， c 的后面可以接字串，这些字串可以取代 n1,n2 之间的行
    - d ：删除，因为是删除啊，所以 d 后面通常不接任何东东
    - i ：插入， i 的后面可以接字串，而这些字串会在新的一行出现(目前的上一行)；
    - p ：打印，亦即将某个选择的数据印出。通常 p 会与参数 sed -n 一起运行～
    - s ：取代，可以直接进行取代的工作哩！通常这个 s 的动作可以搭配正则表达式！例如 1,20s/old/new/g 就是啦！

    ```shell
    #显示sed_test.c(包括行号)，删除文本的34-38行，最后输出到sed_test1.c
    nl sed_test.c | sed -e '34,38d' > sed_test1.c
    ```

    

    ![image-20260910224756598](C:\Users\田庆新\AppData\Roaming\Typora\typora-user-images\image-20260910224756598.png)

    **使用d删除范围内的内容**

    ```shell
    #删除sed_test.c文件的第30行到最后(未持久化)
    tqx@linux-ubuntu:~$ nl sed_test.c | sed '3,$d'
         1  #include <stdio.h>
         2  /**
    ```

    **使用a在第四行后面一行新增字符串：**

    ```shell
    #在第4行追加文本hahahahhaha
    tqx@linux-ubuntu:~$ nl sed_test.c | sed -e '4a hahahahahahhaha'
         1  #include <stdio.h>
         2  /**
         3          sscanf高级用法
         4  */
    hahahahahahhaha
         5  int main1(){
         6          //%s只要遇到\0、\n、空格等会结束匹配
         7          char *ptr="hello1234",buf[10];
         8          int num1,num2;
         9          //%ns 表示需要截取n个字符到相应的内存中
        10          //%nd 表示需要截取n个字符转换成整型存放到相应的内存中
        11          //sscanf(ptr,"%5s%2d%2d",buf,&num1,&num2);
        12          //printf("%s %d %d\n",buf,num1,num2);
        13          //可以通过*跳过n个字符
        14          sscanf(ptr,"%5s%*2d%2d",buf,&num1);
        15          printf("%s %d\n",buf,num1);
        16          return 0;
        17  }
    ```

    **使用i在第四行前面一行追加字符串：**

    ```shell
    #在第四行前面添加字符串wwwwwwwwwwwwwwwww
    tqx@linux-ubuntu:~$ nl sed_test.c | sed -e '4i wwwwwwwwwwwwwwwwwww'
         1  #include <stdio.h>
         2  /**
         3          sscanf高级用法
    wwwwwwwwwwwwwwwwwww
    ```

    **使用换行符\可以达到换行放置多行的效果**

    ```shell
    #在追加放入字符串的同时使用\放置多行
    tqx@linux-ubuntu:~$ nl sed_test.c | sed -e '3a wwwwwwwwwwwwwwwwwww \
    > kkkkkkkkkkkkkkkkkkkk'
         1  #include <stdio.h>
         2  /**
         3          sscanf高级用法
    wwwwwwwwwwwwwwwwwww
    kkkkkkkkkkkkkkkkkkkk
         4  */
         5  int main1(){
         6          //%s只要遇到\0、\n、空格等会结束匹配
         7          char *ptr="hello1234",buf[10];
         8          int num1,num2;
         9          //%ns 表示需要截取n个字符到相应的内存中
        10          //%nd 表示需要截取n个字符转换成整型存放到相应的内存中
        11          //sscanf(ptr,"%5s%2d%2d",buf,&num1,&num2);
        12          //printf("%s %d %d\n",buf,num1,num2);
        13          //可以通过*跳过n个字符
        14          sscanf(ptr,"%5s%*2d%2d",buf,&num1);
        15          printf("%s %d\n",buf,num1);
        16          return 0;
        17  }
    ```

    **使用c进行按行替换：**

    ```shell
    #替换第三行内容
    tqx@linux-ubuntu:~$ nl sed_test.c | sed  -e '3c 你是我的，我是你的谁 \
    > 再多看一眼就会爆炸'
         1  #include <stdio.h>
         2  /**
    你是我的，我是你的谁
    再多看一眼就会爆炸
         4  */
         5  int main1(){
    ```

    **可使用s进行按照正则表达式匹配替换：**

    ```shell
    #将所有main替换成真正的man，g表示全局替换,不写g代表只替换每行的第一个
    tqx@linux-ubuntu:~$ nl sed_test.c | sed -e 's/main/真正的man/g'
         1  #include <stdio.h>
         2  /**
         3          sscanf高级用法
         4  */
         5  int 真正的man1(){
         6          //%s只要遇到\0、\n、空格等会结束匹配
         7          char *ptr="hello1234",buf[10];
         8          int num1,num2;
         9          //%ns 表示需要截取n个字符到相应的内存中
        10          //%nd 表示需要截取n个字符转换成整型存放到相应的内存中
        11          //sscanf(ptr,"%5s%2d%2d",buf,&num1,&num2);
        12          //printf("%s %d %d\n",buf,num1,num2);
        13          //可以通过*跳过n个字符
        14          sscanf(ptr,"%5s%*2d%2d",buf,&num1);
        15          printf("%s %d\n",buf,num1);
        16          return 0;
        17  }
    
        18  int 真正的man2(){
        19          //使用正则表达式进行自动匹配
        20          char buf[]="hgdsdsaodisajDDDSsna129",recv_buf[100];
        21          int num;
        22          //通过正则表达式%[a-z](或者使用[a-i]获取a-i区间内的字符)匹配所有字符串
        23          //如果需要匹配所有大小写字符，写法是：%[A-Za-z]
        24          //适用于不清楚需要截取多少个字符的情况下
        25          //sscanf(buf,"%[a-z]%2d",recv_buf,&num);
        26          //printf("%s %d\n",recv_buf,num);
        27          //可以与*一起使用，表示屏蔽所有a-z的字符
        28          sscanf(buf,"%*[a-zA-Z]%d",&num);
        29          printf("%d\n",num);
        30          return 0;
        31  }
    
        32  int 真正的man(){
    ```

    **可以使用i来直接对文本进行修改：**

    ```shell
    #用-i 替换 -e，可以直接对文本进行修改
    tqx@linux-ubuntu:~$ sed -i 's/main/真正的man/g' sed_test.c
    tqx@linux-ubuntu:~$ cat sed_test.c
    #include <stdio.h>
    /**
            sscanf高级用法
    */
    int 真正的man1(){
            //%s只要遇到\0、\n、空格等会结束匹配
            char *ptr="hello1234",buf[10];
            int num1,num2;
            //%ns 表示需要截取n个字符到相应的内存中
            //%nd 表示需要截取n个字符转换成整型存放到相应的内存中
            //sscanf(ptr,"%5s%2d%2d",buf,&num1,&num2);
            //printf("%s %d %d\n",buf,num1,num2);
            //可以通过*跳过n个字符
            sscanf(ptr,"%5s%*2d%2d",buf,&num1);
            printf("%s %d\n",buf,num1);
            return 0;
    }
    
    int 真正的man2(){
    ```

    

43. 可以修改PATH变量值，添加bash搜索路径(临时)：

    ```bash
    #/home/tqx/linux-learn/path路径下存在可执行文件test_path
    tqx@linux-ubuntu:~/linux-learn/path$ ls
    path.c  test_path
    #在未添加环境变量情况下不能直接调用test_path,bash从PATH路径中无法查询到这个可执行程序
    tqx@linux-ubuntu:~/linux-learn/path$ test_path
    test_path: command not found
    tqx@linux-ubuntu:~/linux-learn/path$ ./test_path
    helloworld !!!
    tqx@linux-ubuntu:~/linux-learn/path$ echo $PATH
    /usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin
    #将当前路径添加到PATH下，之后bash子进程就可以找到该程序执行。这里当然是临时添加，持久化需要修改文件(~/.profile或者~/.bashrc)
    tqx@linux-ubuntu:~/linux-learn/path$ export PATH=$PATH:/home/tqx/linux-learn/path
    tqx@linux-ubuntu:~/linux-learn/path$ !-2
    echo $PATH
    /usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin:/home/tqx/linux-learn/path
    tqx@linux-ubuntu:~/linux-learn/path$ test_path
    helloworld !!!
    #~/.bashrc文件添加环境变量，在执行 .  ~/.bashrc
    118
    119 # 增加自定义别名
    120 #alias cps="cd /usr/include"
    121 #添加环境变量
    122 export PATH=$PATH:/home/tqx/linux-learn/path
    ```

    

44. 显示文件类型：

    ```bash
    file file_name.txt
    tqx@linux-ubuntu:~/linux-learn/param$ file param.sh
    param.sh: Bourne-Again shell script, UTF-8 Unicode text executable
    ```

    

45. 递归删除某一类型文件：

    ```bash
    #删除当前目录及其子目录下所有的.exe文件
    find . -name "*.exe" -delete
    ```

    

46. 显示文件的十六进制形式：

    ```bash
    hexdump [-C...] file.txt	#显示文件的十六进制形式，并输出他们的ASCII
    tqx@linux-ubuntu:~/linux-learn$ hexdump -C windows-test.txt		#输出windows下创建的文件abc，占7个字节s
    00000000  61 0d 0a 62 0d 0a 63                              |a..b..c|
    00000007
    tqx@linux-ubuntu:~/linux-learn$ hexdump -C linux-test.txt		#输出linux创建的文件abc，占6个字节,换行少了\r
    00000000  61 0a 62 0a 63 0a                                 |a.b.c.|
    00000006
    ```

    

47. 格式转换：

    ```bash
    dow2unix file.txt	#将windows、mac系统下的文件转化为unix系统下的格式
    tqx@linux-ubuntu:~/linux-learn$ dos2unix windows-test.txt
    dos2unix: converting file windows-test.txt to Unix format...
    tqx@linux-ubuntu:~/linux-learn$ ls -l
    total 32
    -rwxrwxr-x 1 tqx tqx   40 Sep  5 17:38 alias
    -rwxrwxr-x 1 tqx tqx  356 Sep 11 16:09 bash1
    -rwxrwxr-x 1 tqx tqx  326 Sep 13 16:55 echo.sh
    -rwxrwxr-x 1 tqx tqx   59 Sep  5 17:05 eo
    -rw-rw-r-- 1 tqx tqx    6 Sep 13 17:04 linux-test.txt
    drwxrwxr-x 2 tqx tqx 4096 Sep 12 18:08 param
    drwxrwxr-x 2 tqx tqx 4096 Sep 12 16:45 path
    -rw-rw-r-- 1 tqx tqx    5 Sep 13 17:07 windows-test.txt
    tqx@linux-ubuntu:~/linux-learn$ hexdump -C windows-test.txt		#将该文件转化为unix风格之后，删除了\r字符
    00000000  61 0a 62 0a 63                                    |a.b.c|
    00000005
    ```

    ```bash
    unix2dos file.txt	#将unix下的文件转化为dos、mac风格
    tqx@linux-ubuntu:~/linux-learn$ unix2dos windows-test.txt
    unix2dos: converting file windows-test.txt to DOS format...
    tqx@linux-ubuntu:~/linux-learn$ ls -l
    total 32
    -rwxrwxr-x 1 tqx tqx   40 Sep  5 17:38 alias
    -rwxrwxr-x 1 tqx tqx  356 Sep 11 16:09 bash1
    -rwxrwxr-x 1 tqx tqx  326 Sep 13 16:55 echo.sh
    -rwxrwxr-x 1 tqx tqx   59 Sep  5 17:05 eo
    -rw-rw-r-- 1 tqx tqx    6 Sep 13 17:04 linux-test.txt
    drwxrwxr-x 2 tqx tqx 4096 Sep 12 18:08 param
    drwxrwxr-x 2 tqx tqx 4096 Sep 12 16:45 path
    -rw-rw-r-- 1 tqx tqx    7 Sep 13 17:12 windows-test.txt
    tqx@linux-ubuntu:~/linux-learn$ hexdump windows-test.txt -C		#转换后添加上了\r
    00000000  61 0d 0a 62 0d 0a 63                              |a..b..c|
    00000007
    ```

    

48. 编码转换：

    ```bash
    iconv [options] file	#转换编码格式
    Usage: iconv [OPTION...] [FILE...]
    Convert encoding of given files from one encoding to another.
    
     Input/Output format specification:
      -f, --from-code=NAME       encoding of original text
      -t, --to-code=NAME         encoding for output
    
     Information:
      -l, --list                 list all known coded character sets
    
     Output control:
      -c                         omit invalid characters from output
      -o, --output=FILE          output file
      -s, --silent               suppress warnings
          --verbose              print progress information
    
      -?, --help                 Give this help list
          --usage                Give a short usage message
      -V, --version              Print program version
    ```

    DEMO:

    ```bash
    #将文件gbk.txt 转换为utf8格式：
    iconv -f gb2312 gbk.txt [-t utf-8] -o gbk2utf8.txt
    
    tqx@linux-ubuntu:~/linux-learn$ file gbk.txt	#显示文本格式
    gbk.txt: ISO-8859 text, with no line terminators
    tqx@linux-ubuntu:~/linux-learn$ iconv -f gb2312 gbk.txt -t utf-8 -o gbk2utf8.txt
    tqx@linux-ubuntu:~/linux-learn$ ll
    total 104
    drwxrwxr-x  4 tqx tqx 61440 Sep 13 17:38 ./
    drwxr-xr-x 28 tqx tqx  4096 Sep 13 17:08 ../
    -rwxrwxr-x  1 tqx tqx    40 Sep  5 17:38 alias*
    -rwxrwxr-x  1 tqx tqx   356 Sep 11 16:09 bash1*
    -rwxrwxr-x  1 tqx tqx   326 Sep 13 16:55 echo.sh*
    -rwxrwxr-x  1 tqx tqx    59 Sep  5 17:05 eo*
    -rw-rw-r--  1 tqx tqx     9 Sep 13 17:38 gbk2utf8.txt	#转换后字节数由6个增加到9个
    -rw-rw-r--  1 tqx tqx     6 Sep 13 17:32 gbk.txt
    -rw-rw-r--  1 tqx tqx     6 Sep 13 17:04 linux-test.txt
    drwxrwxr-x  2 tqx tqx  4096 Sep 12 18:08 param/
    drwxrwxr-x  2 tqx tqx  4096 Sep 12 16:45 path/
    -rw-rw-r--  1 tqx tqx     7 Sep 13 17:12 windows-test.txt
    tqx@linux-ubuntu:~/linux-learn$ cat gbk2utf8.txt
    大家好tqx@linux-ubuntu:~/linux-learn$
    tqx@linux-ubuntu:~/linux-learn$ file gbk2utf8.txt`	#转换后的文本格式为utf-8
    gbk2utf8.txt: UTF-8 Unicode text, with no line terminators
    ```

    

49. **数组的使用：**

    ```bash
    #定义数组：括号里面不要有逗号，直接用空格隔开
    array=("abc" "bcd" "efg" "hij" "klm")
    #往数组中追加元素
    array+=("llll")
    ${array[@]}	#迭代数组写法
      7 for item in "${array[@]}" ;do
      8         echo "$item"
      9 done
    
    ${!array[@]}	#迭代数组，使用下标的写法。
    ```

    **demo:**

    ```bash
      1 #!/bin/bash
      2 #数组的定义，使用
      3 array=("abc" "cbd" "efg" "ghi")
      4 array+=("jkl")
      5
      6 echo "下面是直接迭代获取数组元素"
      7 for item in "${array[@]}" ;do
      8         echo "$item"
      9 done
     10
     11 echo "下面是用下标访问的遍历"
     12 declare -i i=0
     13 for i in "${!array[@]}" ; do
     14         echo "第i个元素值 = ${array[$i]}"
     15         i+=1
     16 done
     17 unset array
     18 exit 0
    ```

    

50. 查找命令：

    ```bash
    find [options] [-oa] expression	#-o 表示逻辑或，-a是逻辑与，用于连接两个指令
    find . -type f -o -type d	#查询当前目录下所有的文件以及目录并列出
    find . -iname "apple*"	#忽略大小写查找所有以apple为开头的文件
    find . -empty	#查找空文件
    find . -size +0 -type f #查找所有大小大于0的文件
    find . -size 0 -type f > file	#查找所有文件大小为0的普通文件名称，输出到file文件中
    find . -type d -size +0 -name ".git" -exec rm -rf {} +	#删除所有该目录下名为.git的不为空的文件夹及其内容
    ```

    

51. 复用上一条指令的参数:

    ```bash
    !*	#将上条指令的所有参数复用到本条指令,排除命令名本身
    tqx@LAPTOP-G3KT1I3B$ cp ../trap.sh ./trap.bak	#1、复制指令
    tqx@LAPTOP-G3KT1I3B$ ll !*	#2、ll指令，参数列表复用上一条cp指令的参数
    ll ../trap.sh ./trap.bak
    -rwxrwxrwx 1 tqx tqx 586 Sep 21 20:29 ../trap.sh*
    -rwxrwxrwx 1 tqx tqx 586 Sep 26 17:00 ./trap.bak*
    
    !$ #复用上条指令的最后一个参数
    tqx@linux-ubuntu:~/linux-learn/system_call/exec$ gcc execve.c -o execve
    tqx@linux-ubuntu:~/linux-learn/system_call/exec$ echo !$	#最后一个参数为execve
    echo execve
    execve
    
    !:n #复用上条指令的第n个参数，从0开始是命令本身
    mv test1 test2 test3
    echo !:1   # test1
    echo !:2   # test2
    echo !:3   # test3
    
    !^ #上条指令的第一个参数
    cp a.txt b.txt
    vim !^
    #等价 vim a.txt
    
    !:1-3 #复用从1到3的参数
    echo a b c d
    ls !:1‑3
    # ls a b c
    
    !! # 重复执行上一条指令
    tqx@linux-ubuntu$ echo a b c d
    a b c d
    tqx@linux-ubuntu$ !!
    echo a b c d
    a b c d
    ```

    

52. 复制文件：

    ```bash
    cp [options] ...sources...dirctionay..
    
    options:
    	-p: 保留文件的元数据，包括创建、修改、访问日期，属主，属组等元数据。
    	-r/R: 递归复制，文件夹必须要带这个选项。
    	-d: 如果文件为链接文件，不会解引用去复制被链接的文件，而是复制链接文件
    	-a: 符合选项，等价于: -drp,常用于备份，需要保留文件的所有属性
    	-i: 当文件存在时会提醒是否覆盖选项。 
    	-v: 查看复制过程
    	-b: 复制文件时如果已经存在了文件，先对文件进行备份，再复制文件。该方式默认只会备份一个。
    		等价于： --backup[=CONTROL]，
    		CONTROL：
    			numbered: 该选项会按照数字从1开始进行累计备份多个
    			
    			 none, off
                  never make backups (even if --backup is given)
    
          		 numbered, t
                  make numbered backups
    
          		 existing, nil
                  numbered if numbered backups exist, simple otherwise
    
           		simple, never
                  always make simple backups
    ```

    DEMO:

    ```bash
    tqx@LAPTOP-G3KT1I3B$ cp -p /etc/vconsole.conf ./	#使用-p，拷贝的是链接文件所指向的目标文件
    tqx@LAPTOP-G3KT1I3B$ ll
    total 0
    drwxrwxrwx 1 tqx tqx 4096 Sep 26 18:10 ./
    drwxrwxrwx 1 tqx tqx 4096 Sep 26 16:58 ../
    -rwxrwxrwx 1 tqx tqx  586 Sep 21 20:29 trap.bak*
    -rwxrwxrwx 1 tqx tqx  150 Jan  7  2025 vconsole.conf*	#拷贝后的文件不是链接文件本身
    
    tqx@LAPTOP-G3KT1I3B$ cp -a /etc/vconsole.conf ./	#-a拷贝的是链接文件，保留它的所有属性
    tqx@LAPTOP-G3KT1I3B$ ll
    total 0
    drwxrwxrwx 1 tqx tqx 4096 Sep 26 18:10 ./
    drwxrwxrwx 1 tqx tqx 4096 Sep 26 16:58 ../
    -rwxrwxrwx 1 tqx tqx  586 Sep 21 20:29 trap.bak*
    lrwxrwxrwx 1 tqx tqx   16 Jan  7  2025 vconsole.conf -> default/keyboard
    ```

    --backup=numbered:

    ```bash
    tqx@LAPTOP-G3KT1I3B:/mnt/d/workspace/clion/github-repository/program/linux-learn/shell/cp$ cp --backup=numbered t1 t2
    tqx@LAPTOP-G3KT1I3B:/mnt/d/workspace/clion/github-repository/program/linux-learn/shell/cp$ ls
    t1  t2  t2.~1~  t2~  trap.bak	#会按照~n~后缀进行升序备份多个
    ```

    --backup(-b):

    ```bash
    tqx@LAPTOP-G3KT1I3B:/mnt/d/workspace/clion/github-repository/program/linux-learn/shell/cp$ cp -b t1 t2
    tqx@LAPTOP-G3KT1I3B:/mnt/d/workspace/clion/github-repository/program/linux-learn/shell/cp$ ls
    t1  t2  t2~  trap.bak	#仅会备份一个。
    ```

    

53. ##### 显示/删除进程通信的设施(共享内存、消息队列、信号量数组)信息：

    ```bash
    ipcs [options]	#显示进程通信设施信息
    options:
    	-q: 显示消息队列
    	-m: 共享内存
    	-s: 信号量集合
    	-a: 以上三项
    ipcrm [shm|msg|sem] ID	#删除选项
    ipcrm [options]
    -a: --all删除所有资源
    -M: --shmem-key shmkey,删除某个key的共享内存
    -Q: --queue-key msgkey,删除某个key的消息队列
    -S: --semaphore-key semkey,删除某个key的信号量
    -m: --shmem-id shmid,以id为参数删除共享内存
    -q: --queue-id msgid,以id为参数删除消息队列
    -s: --semaphore-id semid,以id为参数删除信号量
    ```

    ###### demo:

    ```bash
    tqx@LAPTOP-G3KT1I3B$ ipcs -q
    
    ------ Message Queues --------
    key        msqid      owner      perms      used-bytes   messages
    0xba304874 0          tqx        666        0            0
    
    tqx@LAPTOP-G3KT1I3B$ ipcrm -q 0	#删除id为0的消息队列
    tqx@LAPTOP-G3KT1I3B$ ipcs -q
    
    ------ Message Queues --------
    key        msqid      owner      perms      used-bytes   messages
    ```

    ```bash
    tqx@LAPTOP-G3KT1I3B$ ipcs -q
    
    ------ Message Queues --------
    key        msqid      owner      perms      used-bytes   messages
    0xba304874 1          tqx        666        0            0
    
    tqx@LAPTOP-G3KT1I3B$ ipcrm -Q 0xba304874	#以key为参数删除消息队列
    tqx@LAPTOP-G3KT1I3B$ ipcs -q
    
    ------ Message Queues --------
    key        msqid      owner      perms      used-bytes   messages
    
    ```

    

54. ##### size查看二进制文件 [Bob_chat] 在内存中的分区情况：

    ```bash
    tqx@linux-ubuntu$ size Bob_chat
    
    #text 代码段(只读)；
    #data 已初始化的全局变量、静态变量；
    #bss 未初始化的全局变量、静态变量；
    #dec 前几项的总和十进制表示；
    #hex 前几项的总和十六进制表示
       text    data     bss     dec     hex filename
       3460     700      16    4176    1050 Bob_chat
    ```

    

55. 声明执行脚本的程序：

    ```bash
    #声明bash程序执行该脚本
    #!/bin/bash
    #声明sh程序执行
    #!/bin/sh
    ```

    

56. 脚本执行方式：

    ```bash
    #fork新的子进程执行脚本：
    bash test_bash
    ./test_bash
    #当前进程执行脚本：
    . test_bash
    source test_bash
    ```

    

57. 自定义变量(字符串)：

    ```bash
    #定义,注意等号两边不能有空格
    num=10
    echo $num
    unset num	#销毁变量
    
    tqx@linux-ubuntu:~$ num=10+20
    tqx@linux-ubuntu:~$ echo $num
    10+20
    tqx@linux-ubuntu:~$ num='10+20'
    tqx@linux-ubuntu:~$ echo $num
    10+20
    tqx@linux-ubuntu:~$ unset $num
    -bash: unset: `10+20': not a valid identifier
    tqx@linux-ubuntu:~$ unset num
    tqx@linux-ubuntu:~$ echo $num
    ```

    

58. 从标准输入读取字符串赋值给变量name(scanf的作用)：

    ```bash
    read name	#scanf的作用，从终端获取输入的字符串，赋值给name
    
    tqx@linux-ubuntu:~$ read name
    tqx
    tqx@linux-ubuntu:~$ echo $name
    tqx
    ```

    

59. 设置变量为常量：

    ```bash
    readonly name="str"	#设置的name后续只读不能修改
    
    tqx@linux-ubuntu:~$ readonly name="蔡徐坤"
    tqx@linux-ubuntu:~$ echo $name
    蔡徐坤
    tqx@linux-ubuntu:~$ read name
    hahaha
    -bash: name: readonly variable
    tqx@linux-ubuntu:~$ unset name	#常量不能使用unset删除
    -bash: unset: name: cannot unset: readonly variable
    ```

    

60. 声明整型变量：

    ```bash
    #2种方式都可以
    declare -i num=100
    typeset num=20
    
    tqx@linux-ubuntu:~$ declare -i num=10+20
    tqx@linux-ubuntu:~$ echo $num
    30
    tqx@linux-ubuntu:~$ typeset num=100
    tqx@linux-ubuntu:~$ echo $num
    100
    tqx@linux-ubuntu:~$ typeset num=100+20
    tqx@linux-ubuntu:~$ !-2
    echo $num
    120
    ```

    

61. 输出字符串的子串、长度：

    ```bash
    tqx@linux-ubuntu:~$ str="abcdefs"
    tqx@linux-ubuntu:~$ echo ${#str}	#输出字符串的长度，等价于${#str[0]}
    7
    tqx@linux-ubuntu:~$ echo ${#str[0]}
    7
    tqx@linux-ubuntu:~$ echo ${str:1,4}	#zsh扩展用法，逗号表达式，结果与echo ${str:4}相同
    efs
    tqx@linux-ubuntu:~$ echo ${str:4}	#与上述指令相同，都是从下标为4开始截取到字符串末尾
    efs
    tqx@linux-ubuntu:~$ echo ${str:1:4}	#截取子串，从下标第1个，截取4个字符
    bcde
    ```

62. 查看环境变量：

    ```bash
    env	#列出所有的环境变量
    export name="str"	#将name设置到当前进程的环境变量中。该变量可以被fork子进程继承
    export -p #列出所有环境变量中的参数值
    export -n [name] #删除名称为name的环境变量。
    #注意：如果使用脚本在当前进程设置环境变量，执行命令必须使用: . 或者source ，使其在当前进程执行。如果使用bash或者./执行
    #会开启新的子进程执行，当前进程作为父进程不会有任何改变。
    #以上指令只会在当前进程存活时有效，持久化就需要写入~/.bashrc（登录用户有效），或者/etc/profile(全局有效),当用户登录开启shell进程时会自动调用这几个脚本文件
    ```

63. 脚本内获取参数：

    ```bash
    $#	#获取参数的个数
    $*	#获取参数列表(省去了第一个参数，也就是执行脚本的命令)，受$IFS的影响，如果IFS值发生变化，参数之间的空格也会变化，推荐使用$@
    $@	#获取参数列表,添加双引号后不受环境变量$IFS的影响，始终会给参数之间添加空格
    $0,$1...	#获取对应下标的参数，从0开始
    $?	#获取上一句指令执行是否正常，正常输出0
    $$	#获取当前shell的进程号
    ```

    ```bash
      1 #!/bin/bash
      2 echo $#
      3 echo $*
      4 echo $?
      5 echo "以下是参数列表"
      6 echo $0
      7 echo $1
      8	echo $$	
    ```

    输出格式如下：

    ```bash
    tqx@linux-ubuntu:~/linux-learn/param$ ./param.sh hallo 你好   heihieiei
    3	#参数的个数，不包括执行脚本的指令
    hallo 你好 heihieiei	#参数列表，去掉了执行脚本的指令
    0	#上一句脚本正常执行
    以下是参数列表
    ./param.sh	# $0下标为0的参数
    hallo	#下标为1的参数
    96256	#当前进程号
    
    tqx@linux-ubuntu:~/linux-learn/param$ ls > ls-`date +%F`-$$.log		#生成以日期+进程号格式的日志文件
    tqx@linux-ubuntu:~/linux-learn/param$ ls
    ls-2026-09-14-99118.log  param2.sh  param.sh
    tqx@linux-ubuntu:~/linux-learn/param$ cat ls-2026-09-14-99118.log
    ls-2026-09-14-99118.log
    param2.sh
    param.sh
    ```

    

64. 特殊符号：

    ```bash
    #指令：``用于执行内部指令，等同于$()
    `date`
    $(pwd)
    #$name:用于获取变量name的值
    echo $name
    #"":弱引用类型，被包裹的字符串中使用特殊字符可以被解析
    echo "$name"	#可以被解释成取name的值
    #可以使用转义字符\来解除echo对变量的解析，等价于使用''
    echo "\$PATH"
    # '':强引用类型，只会把内容当成字符串输出
    echo '$name' #输出$name
    # ( 内容 )：fork子进程去执行括号内的脚本
    # { 内容; }:当前进程执行该脚本
    ```

    DEMO：

    ```bash
    tqx@linux-ubuntu:~$ echo "$PATH"
    /usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin:/home/tqx/linux-learn/path
    
    tqx@linux-ubuntu:~$ echo "\$PATH"
    $PATH
    ```

    

    ```bash
      1 #!/bin/bash
      2 echo "测试source与.命令，执行sh文件"
      3
      4 echo "HOME =  $HOME"
      5 echo "今天 = `date`"
      6 echo "当前目录= $(pwd)"
      7
      8 name=student
      9 ( name="张三"
     10 echo "子进程= $name" )
     11 echo "当前进程 = $name"
     12 { name="李四";echo "当前进程{} = $name"; }
     13 echo "当前进程2 = $name"
     
    ```

    输出如下：

    ```bash
    tqx@linux-ubuntu:~/linux-learn$ ./echo.sh
    测试source与.命令，执行sh文件
    HOME =  /home/tqx
    今天 = Sun 13 Sep 2026 04:47:32 PM CST
    当前目录= /home/tqx/linux-learn
    子进程= 张三	# (  )内容在子进程执行，变量不会影响当前进程
    当前进程 = student
    当前进程{} = 李四	# {  }内容在当前进程执行，变量值改变
    当前进程2 = 李四
    ```

    引号的用法：

    ```bash
    #!/bin/bash
    #引号的使用
    
    myparam=大家好才是真的好
    echo 不带引号的= $myparam
    echo "双引号的=$myparam"
    echo '单引号的=$myparam'
    echo "带转义字符\\的：\$myparam"
    echo 请输入要修改的变量值:
    read myparam
    echo '当前myparam的变量值=' "$myparam"
    exit 0;
    
    #输出
    tqx@linux-ubuntu:~/linux-learn/param$ !-2
    ./param2.sh
    不带引号的= 大家好才是真的好
    双引号的=大家好才是真的好
    单引号的=$myparam
    带转义字符\的：$myparam
    请输入要修改的变量值:
    我是谁
    当前myparam的变量值= 我是谁
    ```

    

65. 测试文件存不存在：

    ```bash
    test [options] file 	#测试文件是否满足条件，满足返回0，不满足返回1
    #可以使用[ [options] file ]形式,与上述相同
    
    #选项很多，列出几项：
    -e	: 	是否存在
    -f	:	是否为普通文件
    -d	:	是否为目录
    -b	:	是否为块设备
    -c	:	是否为字符设备
    -r	:	是否可读（当前用户的权限）
    -w	:	是否可写（当前用户的权限）
    -x	：	是否可执行（当前用户的权限）
    -L	：	是否为链接文件
    -s	：	是否内容非空
    ```

    ```bash
    tqx@linux-ubuntu:~/linux-learn$ test -e /etc/file
    tqx@linux-ubuntu:~/linux-learn$ echo $?
    1
    
    tqx@linux-ubuntu:~/linux-learn$ test -e ./windows-test.txt
    tqx@linux-ubuntu:~/linux-learn$ echo $?
    0
    
    tqx@linux-ubuntu:~/linux-learn$ test -f windows-test.txt
    tqx@linux-ubuntu:~/linux-learn$ echo $?
    0
    
    tqx@linux-ubuntu:~/linux-learn$ test -d windows-test.txt
    tqx@linux-ubuntu:~/linux-learn$ !-2
    echo $?
    1
    ```

    使用[]表达式形式：

    ```bash
    #注意 [ expression ]，方括号与表达式之间必须有空格 
    tqx@linux-ubuntu:~/linux-learn$ [ -e windows-test.txt ]	#等价于： test -e windows-test.txt
    tqx@linux-ubuntu:~/linux-learn$ echo $?
    0
    ```

    

66. 逻辑运算符&&、||、！：

    ```bash
    #可以使用逻辑运算符&&、||，!，效果等同于其他语言
    tqx@linux-ubuntu:~/linux-learn/if$ [ -e ./name ] || echo "ttt"
    ttt
    tqx@linux-ubuntu:~/linux-learn/if$ [ -e /home ] || echo "ttt"
    
    tqx@linux-ubuntu:~$ [ -e /home ] && echo "home"; [ -f /home ] && echo "dir"
    home
    tqx@linux-ubuntu:~$ [ -e /home ] && echo "home"; [ -d /home ] && echo "dir"
    home
    dir
    # !非运算符，表达式取反，取反后为真执行，为假不执行
    tqx@linux-ubuntu:~/linux-learn/if$ [ ! -e /home ] && echo "11"	#测试/home存不存在，结果取反之后为假
    tqx@linux-ubuntu:~/linux-learn/if$ [ ! -f /home ] && echo "11"	#测试/home是不是普通文件，结果取反后为真
    11
    
    # && || 连起来使用，利用短路求值的特性来控制语句的执行：
    tqx@linux-ubuntu:~/linux-learn/shell/if$ ls
    and_or.sh  case.sh  if-expression.sh  if.sh  test-file
    #test-file为目录，所以下面语句的前两句输出为真，||遇到真短路，最后echo语句不会执行
    tqx@linux-ubuntu:~/linux-learn/shell/if$ [ -f case.sh ] && [ -d test-file ] || echo "nono"
    #前两句为假，会执行到最后
    tqx@linux-ubuntu:~/linux-learn/shell/if$ [ -f case.sh ] && [ -f test-file ] || echo "nono"
    nono
    
    # && 与 ||结合可以达到三目运算符的效果：
    # [ expression ] && command(为真时执行) || command(为假时执行)
    #[ -f case.sh ] 测试为真，输出第一个echo，|| 左边的语句为真，不会再执行第二个echo
    tqx@linux-ubuntu:~/linux-learn/shell/if$ [ -f case.sh ] && echo "is nornal file" || echo "is dir"
    is nornal file
    #[ -d case.sh ]测试为假，&&短路求值，第一个echo不会执行，||左边结果为false，会继续执行第二个echo
    tqx@linux-ubuntu:~/linux-learn/shell/if$ [ -d case.sh ] && echo "is nornal file" || echo "is dir"
    is dir
    ```

    

67. 条件运算符：

    - if:

      ```bash
      #格式：
      if expression ; then 	#或者then另起一行，去掉分号
      ....
      elif expression; then
      ...
      else 
      ...
      fi
      ```

      **demo:**

      ```bash
        1 #!/bin/bash
        2
        3 #表达式条件判断用法
        4
        5 if [ 10 -gt 20 ]
        6 then
        7         echo "10 > 20"
        8 else
        9         echo "10 < 20"
       10 fi
       11
       12 declare -i n1=10+20
       13 declare -i n2=20+10
       14
       15 if [ $n1 -gt $n2 ]; then
       16         echo "10+20 > 20+10"
       17 elif [ $n1 -lt $n2 ]; then
       18         echo "10+20 < 20+10"
       19 elif [ $n1 -eq $n2 ]; then
       20         echo "10+20 = 20+10"
       21 else
       22         echo "error"
       23         exit 1
       24 fi
       25
       26 exit 0
      ```

      

    - case:

      ```bash
      case 变量 in 
      pattern [ | pattern...] ) ....;;	#case可以使用逻辑运算符|进行多个参数并在一起比较,结束标志是双分号
      pattern [ | pattern ...] ) ....;;
      ...
      esac	#结束标志
      ```

      **demo:**

      ```bash
        1 #!/bin/bash
        2
        3 #case语句使用
        4 echo "现在是早上吗？请输入yes/no"
        5 read config
        6 case "$config" in
        7
        8 'yes' | 'y' )   echo "您输入的是yes";;
        9 'no' | 'n' )    echo "您输入的是no";;
       10 * )     echo "输入不合法";;
       11
       12 esac
       13
       14 exit 0
      ```

      如果出现的字母较固定且要匹配的情况比较多，可通过[]进行多种样式匹配：

      ```bash
      #!/bin/bash
      
      #case语句使用
      echo "现在是早上吗？请输入yes/no"
      read config
      case "$config" in
      
      [yY] | [yY][eE][sS] )   echo "您输入的是yes";;	#[yY][eE][sS]包含了大小写字母的组合形式
      [nN] | [nN][oO] )       echo "您输入的是no";;
      * )     echo "输入不合法";;
      
      esac
      
      exit 0
      ```

      

68. 循环语句：

    - for:

      **第一种：**

      ```bash
      for 变量 in values 
      do
      ...
      done
      ```

      **demo:**

      ```bash
        1 #!/bin/bash
        2 #for循环
        3 array=(foo,bar,fu,mm)
        4 for fn in $array; do
        5         echo $fn
        6 done
        7 path=/home/tqx/
        8 for file in $(ls "$path"*); do
        9         [ -e "$file" ] || continue	#文件不存在直接跳过
       10         if [ -f "$file" ]; then
       11                 echo "$file is file"
       12         elif [ -d "$file" ];then
       13                 echo "$file is dir"
       14         else
       15                 echo "^_^"
       16         fi
       17
       18 done
       19
       20 exit 0
      ```

      **第二种：**

      ```bash
      #与其他语言类似，不同的是使用双括号
      for ((初值;循环条件;步长));do
      ...
      done
      ```

      **demo:**

      ```bash
        1 #!/bin/bash
        2 #for循环第二种方式，迭代一定次数
        3
        4 declare -i sum
        5
        6 for((i=0;i<100;i=i+1)); do
        7
        8         sum=$sum+i
        9 done
       10 echo "sum = $sum"
       11 exit 0
      ```

      

    - **while:**

      ```bash
      while [ expression ];do	#条件成立，执行循环体
      ...
      done
      ```

      **demo:**

      ```bash
        1 #!/bin/bash
        2 #while循环用法
        3 declare -i sum=0
        4 declare -i i=1
        5
        6 while [ "$i" -le  100 ]; do		#从1加到100
        7         sum+=i	#可以使用+=，或者使用变量相加，但不能使用++、--。
        8         i=i+1	#等号左右两边不能有空格
        9 done
       10 echo "sum = $sum"
       11 exit 0
      ```

    - **until循环：**

      ```bash
      until [ expression ];do	#与while相反，条件不成立，执行循环体
      ...
      done
      ```

      **demo:**

      ```bash
        1 #!/bin/bash
        2 #until循环使用，与while循环相反，当满足条件时跳出循环
        3
        4 declare -i sum=0
        5 declare -i i=1
        6
        7 until [ "$i" -gt 100 ]; do
        8
        9         sum+=i
       10         i+=1
       11 done
       12 echo "sum =$sum"
       13 exit 0
      ```

      

69. 函数的使用：

    ```bash
    function 函数名 (){	#function 关键字可省略
    	#函数体，遵循shell语法,参数通过$1/$2/$n等获取
    }
    #在声明函数之后可以在后面调用该函数
    ```

    demo:

    ```bash
      1 #!/bin/bash
      2 #函数的简单用法
      3
      4 function is_dir(){
      5         if [ $# -lt 1 ]; then
      6                 echo "参数个数不足"
      7                 return 1;
      8         elif [ ! -d $1 ];then
      9                 echo "不是一个目录"
     10                 return 2;
     11         else
     12                 return 0;
     13         fi
     14 }
     15
     16 echo "请输入你要查询的目录路径:"
     17 read dir
     18
     19 is_dir $dir
     20 echo "$dir 查询结果= $?"
    ```

    ```bash
      1 #!/bin/bash
      2#两数相加
      3 function add(){
      4         if [ $# -ne 2 ];then
      5                 echo "参数个数不正确"
      6                 return 1;
      7         elif [ $1  -gt 1000 ] || [ $2 -gt 1000 ] ;then
      8                 echo "请输入不超过1000的正整数"
      9                 return 1;
     10         fi
     11         local sum=$(( $1 + $2 ))	#使用$(( ... ))表达式，可以执行算术运算，并且可以将结果赋值给其他变量
     12         echo "$sum"
     13         return 0;
     14 }
     15
     16 declare -i n1 n2
     17 echo "请输入2个要相加的数字"
     18 read n1 n2
     19 ret=$(add $n1 $n2)	# $() 用于捕获函数、可执行脚本的输出结果，赋值给变量ret
     20 echo "$n1+$n2 = $ret"
    ```

    ```bash
    1 #!/bin/bash
      2
      3 function sum_all(){
      4         if [ $# -ne 1 ]; then
      5                 echo "请输入参数"
      6                 return 1;
      7         elif [ $1 -lt 0 ] || [ $1 -gt 100 ];then
      8                 echo "请输入0~100内的数字"
      9                 return 1;
     10         fi
     11         declare -i sum=0
     12         for ((i=0;i <= $1;i+=1));do
     13                 sum+=i;
     14         done
     15         echo "$sum"
     16         return 0
     17 }
     18
     19 declare -i n1
     20 echo "请输入要累加的数"
     21 read n1
     22 sum_all $n1
     23 ret=$(sum_all $n1)
     24 echo "结果= $ret"
    ```

    

70. 表达式求值：

    ```bash
    $(( exp ))	#可以在exp中执行算术逻辑运算，并且结果可输出、可赋值,等价于expr exp
    tqx@linux-ubuntu:~/linux-learn/shell/function$ echo "$(( 1+2 ))"
    3
    tqx@linux-ubuntu:~/linux-learn/shell/function$ ret=$(( 3+10 )) && echo "$ret"
    13
    tqx@linux-ubuntu:~/linux-learn/shell$ x=$(( 10 | 20 ))
    tqx@linux-ubuntu:~/linux-learn/shell$ echo $x
    30
    #使用expr命令进行计算
    tqx@linux-ubuntu:~/linux-learn/shell$ declare -i x=100
    tqx@linux-ubuntu:~/linux-learn/shell$ x=`expr $x + 1`
    tqx@linux-ubuntu:~/linux-learn/shell$ echo $x
    101
    ```

    

71. 条件判断：

    ```bash
    (( exp ))	#仅仅判断表达式的算术运算的真假，仅返回$?
    # (( 10 > 20 ))结果为假，$?不为0，会执行else分支，输出第二个echo
    tqx@linux-ubuntu:~/linux-learn/shell/function$ if (( 10 > 20 ));then echo "10 > 20 ";else echo "10 < 20";fi
    10 < 20
    ```

    

72. test测试：

    ```bash
    [ exp ]		#等价于 test exp，是test的更简洁可读的写法
    #条件测试 10 不等于20，为真返回第一个echo
    tqx@linux-ubuntu:~/linux-learn/shell/function$ [ 10 -ne 20 ] && echo "10 != 20" || echo "10 ==20"
    10 != 20
    ```

    

73. 空命令：

    ```bash
    :	#空命令，在条件判断里面可以当做true的简化写法，因为是内置命令，处理起来比true要快，但可读性差，while : 等价于while true
    #: = true,什么也不输出
    tqx@linux-ubuntu:~/linux-learn/shell/function$ [ 10 -ne 20 ] && : || echo "10 ==20"
    tqx@linux-ubuntu:~/linux-learn/shell/function$
    ```

    

74. eval:

    ```bash
    #重新对后面的字符串进行解析，执行,用法类似于C语言的宏
    foo=10
    x=foo
    y=\$$x
    echo $y		#输出$y
    eval y=\$$x
    echo $y		#输出10
    ```

    ```bash
    tqx@linux-ubuntu:~/linux-learn/shell/function$ foo=10
    tqx@linux-ubuntu:~/linux-learn/shell/function$ x=foo
    tqx@linux-ubuntu:~/linux-learn/shell/function$ y="$"$x
    tqx@linux-ubuntu:~/linux-learn/shell/function$ echo $y
    $foo
    
    tqx@linux-ubuntu:~/linux-learn/shell/function$ eval echo \$$x
    10
    tqx@linux-ubuntu:~/linux-learn/shell/function$ eval y=\$$x
    tqx@linux-ubuntu:~/linux-learn/shell/function$ echo $y
    10
    #经典写法：取集合最后一个元素,等价于内置函数：${!#}
    tqx@linux-ubuntu:~/linux-learn/shell/function$ set -- 10 20 30 40
    tqx@linux-ubuntu:~/linux-learn/shell/function$ eval echo \$$#
    40
    tqx@linux-ubuntu:~/linux-learn/shell/function$ echo ${!#}
    40
    ```

    

75. printf:

    ```bash
    #用法与c相同，同样是： 输出格式 输出列表...
    tqx@linux-ubuntu:~/linux-learn/shell$ printf "%s%d\n" "你好" 10
    你好10
    ```

    

76. set:

    ```bash
    #设置参数变量,后面可通过$n获取参数列表
    set param1 param2 ....
    #设置了2个参数，第二条指令是获取第二个参数date
    tqx@linux-ubuntu:~/linux-learn/shell$ set number date
    tqx@linux-ubuntu:~/linux-learn/shell$ echo $2
    date
    ```

    

77. shift:

    ```bash
    #将参数列表全部左移一位，这样$1被丢弃，$2变$1，$3变$2...($0不会改变，因为它是脚本执行命令)。移动后$@、$#、$*也会相应改变
    shift [n] 	#n为左移的次数，不写就是1次，
    #设置了2个参数
    tqx@linux-ubuntu:~/linux-learn/shell$ set number date
    tqx@linux-ubuntu:~/linux-learn/shell$ echo $2
    date
    
    tqx@linux-ubuntu:~/linux-learn/shell$ shift		#左移一位
    tqx@linux-ubuntu:~/linux-learn/shell$ echo $2	#最左边的$1被丢弃，$2变$1,输出第二个参数为空
    
    tqx@linux-ubuntu:~/linux-learn/shell$ echo $1 	# $1是之前的$2
    date
    #进行左移2次
    tqx@linux-ubuntu:~/linux-learn/shell$ set n1 n2 n3 n4
    tqx@linux-ubuntu:~/linux-learn/shell$ shift 2
    tqx@linux-ubuntu:~/linux-learn/shell$ echo $1
    n3
    tqx@linux-ubuntu:~/linux-learn/shell$ echo $#	#最初的4个参数移动后变成2个
    2
    
    tqx@linux-ubuntu:~/linux-learn/shell$ echo "$@"
    n3 n4
    ```

    

78. 信号处理trap：

    ```bash
    trap [command] signal	#针对某一个signal触发时执行的handler
    -command: 要执行的指令。
    		  为空时表示忽略该信号的处理，此时执行信号的默认处理机制。
    		  设置为： - 时，表示重置信号为其默认处理机制
    -signal:具体的信号，可通过trap -l 命令查看。重要的几种如下(括号内为信号编号)
    	HUP(1):	挂起，因中断掉线或用户退出引起。
    	INT(2):	中断。按下CTRL+C
    	QUIT(3): 退出。按下ctrl+\
    	ABRT(6): 中止。因某些严重的执行错误引起。
    	ALAM(14): 报警。用来处理超时
    	TERM(15): 终止。系统关机时触发。
    ```

    ###### DEMO:

    ```BASH
      1 #!/bin/bash
      2 # trap的使用
      3
      4 file_name=`date +%F`-$$.log
      5 declare config=1
      6 #设置中断信号处理
      7 #trap "rm -rf $file_name" INT
      8 trap config=0 INT	#设置INT信号的中断处理，具体操作是将config设置为0
      9 echo "正在创建测试文件 : $file_name"
     10 touch $file_name
     11 echo "文件创建成功"
     12
     13 while [ -f $file_name ] && [ $config -gt 0 ] ;do	#当日志文件存在且config值大于0时，一直循环
     14         echo "文件存在，循环中...\n"
     15         ls >> $file_name
     16         sleep 1
     17 done
     18
     19 echo "第一个中断处理程序执行完毕"
     20
     21 #command 为空表示忽略某个信号，不设置handler，即进行默认的处理
     22 trap INT
     23 while : ;do		#死循环处理
     24         echo "正在进行第二个循环..."
     25         sleep 1
     26 done
     27	# 第二个中断处理INT信号为忽略，不进行特殊处理，此时会执行INT的默认处理，ctrl+c为立即退出当前进程，后面这条echo不会执行
     28 echo "程序退出"
    ```

    执行结果：

    ```bash
    tqx@linux-ubuntu:~/linux-learn/shell$ ./trap.sh
    正在创建测试文件 : 2026-09-20-114300.log
    文件创建成功
    文件存在，循环中...\n
    文件存在，循环中...\n
    文件存在，循环中...\n
    文件存在，循环中...\n
    ^C第一个中断处理程序执行完毕
    正在进行第二个循环...
    正在进行第二个循环...
    正在进行第二个循环...
    正在进行第二个循环...
    正在进行第二个循环...
    ^C
    ```

    

79. find指令查询：

    ```bash
    find [path][options][tests][actions]
    -path:	路径，绝对路径或者相对路径
    -atime N : 文件在N天之前被最后访问过
    -mtime N : 文件在N天之前被最后修改过
    -name pattern: 匹配名称为pattern的文件，pattern可以用正则表达式匹配，最好用双引号括起来
    -newer otherfile: 比otherfile更新的文件。
    -type [t]: 文件类型为t，类型包括字符设备c、块设备b、文件夹d、普通文件f等
    -user username：文件拥有者为username
    -exec command : 执行后面的指令。该命令是一个嵌入式指令，必须使用\;结束，用来表示该条指令的结束。
    				魔术字符串：{}为-exec或者-ok的一个特殊类型参数，执行时用当前文件的完整路径取代。
    -ok command: 与-exec类似，但在执行指令前会针对每个要处理的文件，提示用户进行确认，同样必须使用\;结束。
    -print：打印文件名。
    -ls：对当前文件使用ls-dils
    
    -o： or
    -a： and
    -not： !
    #可使用()进行优先级的重排列,由于()在shell中有子进程执行的用法，在这里进行对其进行\转移
    #如下指令是找出名称是下划线开头或者比fork1更新的，并且类型是普通文件的所有文件。
    find . \( -name "_*" -o -newer "fork1" \) -type f -print
    #下面这条语句实现查找名称以wait开头的普通文件，并且将他们详细信息列出来：
    #其中 {} 表示当前文件的完整路径。
    # {} \; 这种写法会逐个文件fork()一个进程执行，适合单个文件处理
    find . -name "wait*" -type f -exec ls -l {} \;
    #下方这种写法会先遍历，遍历结束后在fork()一个子进程批量处理，进程切换开销小，推荐使用{} +,但是+后面不能追加参数；
    #如果{}不在指令末尾，而是在中间，只能使用 {} ..\;
    find . -name "wait*" -type f -exec ls -l {} +
    #下面这种方式只能使用 {} \;而不能使用 {} + 
    find . -type f -exec mv {} demo/ \;
    
    tqx@LAPTOP-G3KT1I3B$ find . -name "wait*" -type f -exec ls -l {} \;
    -rwxrwxrwx 1 tqx tqx 16376 Sep 22 16:27 ./waitpid
    -rwxrwxrwx 1 tqx tqx 588 Sep 22 16:27 ./waitpid.c
    -rwxrwxrwx 1 tqx tqx 523 Sep 22 15:41 ./wait_nornal.c
    -rwxrwxrwx 1 tqx tqx 16272 Sep 22 15:49 ./wait_signal
    -rwxrwxrwx 1 tqx tqx 597 Sep 22 15:49 ./wait_signal.c
    ```

    

80. 通用正则表达式解析器(general regular expression parser ---grep):

    ```bash
    grep [options] pattern [files] #按照条件搜索匹配表达式的字符串。
    options：
    	-c：只输出匹配行的数量，而不输出匹配的行。
    	-E：启用扩展表达式
    	-h：取消每个输出行的普通前缀，不输出它的文件名。
    	-i：忽略大小写
    	-l: 只列出输出行的文件名，不列出具体的行
    	-v: 反向匹配，即不匹配pattern的行输出。
    ```

    DEMO：

    ```bash
    #grep -h ...
    tqx@LAPTOP-G3KT1I3B:/mnt/d/workspace/clion/github-repository/program/linux-learn/system_call$ grep -hr fork ./
    # but without wasting forks for bash or zsh.
                 # Try only shells that exist, to save several forks.
    @%:@ Set @S|@? to STATUS, without forking.
    @%:@ global @S|@as_val. Take advantage of shells that can avoid forks. The arguments
    # but without wasting forks for bash or zsh.
    @%:@ Set @S|@? to STATUS, without forking.
    @%:@ global @S|@as_val. Take advantage of shells that can avoid forks. The arguments
    # but without wasting forks for bash or zsh.
                 # Try only shells that exist, to save several forks.
    @%:@ Set @S|@? to STATUS, without forking.
    @%:@ global @S|@as_val. Take advantage of shells that can avoid forks. The arguments
    # but without wasting forks for bash or zsh.
    @%:@ Set @S|@? to STATUS, without forking.
    @%:@ global @S|@as_val. Take advantage of shells that can avoid forks. The arguments
    grep: ./process/forks/fork: binary file matches
            if((pid = fork()) < 0 ){
                    printf("父进程fork(),子进程ID = %d\n",pid);
            //当fork()完成后，会生成子进程共同执行该代码，一共2个进程执行，所以这条输出会生成2条。
    grep: ./process/forks/fork1: binary file matches
            if((pid = fork()) <0){
    grep: ./process/forks/fork_create5: binary file matches
                    if((pid = fork()) < 0 )
    grep: ./process/wait/waitpid: binary file matches
            if((pid = fork()) <0)
            if((pid = fork()) <0)
    grep: ./process/wait/wait_signal: binary file matches
            if((pid = fork()) <0)
    #grep -r ...  
    tqx@LAPTOP-G3KT1I3B:/mnt/d/workspace/clion/github-repository/program/linux-learn/system_call$ grep -lr fork .
    ./file/a.txt
    ./file/b.txt
    ./process/forks/fork
    ./process/forks/fork.c
    ./process/forks/fork1
    ./process/forks/fork1.c
    ./process/forks/fork_create5
    ./process/forks/fork_create5.c
    ./process/wait/waitpid
    ./process/wait/waitpid.c
    ./process/wait/wait_nornal.c
    ./process/wait/wait_signal
    ./process/wait/wait_signal.c
    ```

    ###### 正则表达式：

    - **^ : 匹配一行的开头：**

    ```bash
    #输出以int开头的那一行
    tqx@LAPTOP-G3KT1I3B:/mnt/d/workspace/clion/github-repository/program/linux-learn/system_call$ grep ^int std/stdin.c
    int main(){
    ```

    - **$:匹配结尾：**

      ```bash
      #输出以 写为末尾的行：
      tqx@LAPTOP-G3KT1I3B$ grep 写$ std/stdin.c
      //通过read、write针对标准输入(0)、输出(1)、错误(2)进行读写
      ```

      

    - . : 任意单个字符：

      ```bash
      #输出以 写为结尾的，倒数第二个字符为任意字符的行：
      tqx@LAPTOP-G3KT1I3B$ grep .写$ std/stdin.c
      //通过read、write针对标准输入(0)、输出(1)、错误(2)进行读写
      
      #输出以任意前两个字符开头，第三个字符为t的行：
      tqx@LAPTOP-G3KT1I3B$ grep ^..t std/stdin.c
      int main(){
      ```

      

    - [] : 匹配方括号范围内任意的一个字符，如果不希望匹配该范围内的任意字符，在其中添加^:

      ```bash
      #匹配不以/或者#开头的行：
      tqx@LAPTOP-G3KT1I3B$ grep ^[^/#] std/stdin.c
      int main(){
              char buf[128];
              int r_len = read(0,buf,sizeof(buf));
              if(write(1,buf,r_len) != r_len){
                      char msg[] = "写入的字节数不正确";
                      write(2,msg,strlen(msg));
              }
              return 0;
      }
      ```

    - 数字类[:digit:]：

      ```bash
      #[:digit:]表示任意数字，使用时需要添加[]表示范围
      tqx@LAPTOP-G3KT1I3B$ grep [[:digit:]] std/stdin.c
      //通过read、write针对标准输入(0)、输出(1)、错误(2)进行读写
              char buf[128];
              int r_len = read(0,buf,sizeof(buf));
              if(write(1,buf,r_len) != r_len){
                      write(2,msg,strlen(msg));
              return 0;
      ```

      

    - 字母类[:alpha:]：

      ```bash
      #表示任意大小写字母：
      #查询以任意字母开头
      tqx@LAPTOP-G3KT1I3B$ grep ^[[:alpha:]] std/stdin.c
      int main(){
      ```

      ###### 剩余的正则匹配还有：

    - 大写字母[:upper:]

    - 小写字母[:lower:]

    - 字母+数字类[:alnum:]

    - 空格、制表符：[:space:]与[:blank:]

    - 可输出字符[:print:]

    - 十六进制数字[:xdigit:]

    - ascii字符[:ascii:]...

      **使用了-E选项后，可以使用如下正则表达式的扩展选项。由于他们都是特殊字符，在使用时必须以\对其进行转义:**

      - ? : 匹配一次或者0次：

      - *: 匹配0次或多次。

      - +：最少匹配一次

      - {n}: 必须匹配n次

      - {n,}:最少匹配n次

      - {n,m}:匹配n到m次，包含n与m

        ###### DEMO:

        ###### 1、匹配单词长度在4-10之间的字符串：

        ```bash
        tqx@LAPTOP-G3KT1I3B$ grep -E [a-z]\{4,10\} std/stdin.c
        #include <unistd.h>
        #include <stdlib.h>
        #include <string.h>
        //通过read、write针对标准输入(0)、输出(1)、错误(2)进行读写
        int main(){
                char buf[128];
                int r_len = read(0,buf,sizeof(buf));
                if(write(1,buf,r_len) != r_len){
                        char msg[] = "写入的字节数不正确";
                        write(2,msg,strlen(msg));
                return 0;
        ```

        ###### 2、匹配长度为4的字符串，并且以空格左右隔开：

        ```bash
        tqx@LAPTOP-G3KT1I3B$ grep -E [[:space:]][a-z]\{4\}[[:space:]] std/stdin.c
                char buf[128];
                        char msg[] = "写入的字节数不正确";
        ```

        

81. ##### 参数扩展(花括号{}):

    - ###### 算数扩展，完成简单的算术运算：

      ```bash
        1 #!/bin/bash
        2 i=0
        3 while [ "$i" -ne 10 ];do
        4         echo $i
        5         i=$(( $i+1 ))	#对i进行+1运算，等价于 i+=1;
        6 done
      ```

    - ###### 字符串拼接出现歧义，使用{}来保证变量的语义：

      ```bash
        1 #!/bin/bash
        2
        3 for i in 1 2
        4 do
        5 echo ${i}_name	#示例中使用{}括起来表示取参数的值为$i，而不是$i_name
        6 done
      ```

    - ###### ${\#param}:获取变量的长度：

      ```bash
        1 #!/bin/bash
        2 foo=barrrrrr
        3 echo ${#foo}	#输出结果为8，表示foo变量的长度
        4 exit 0
      ```

      

    - ###### ${param:-default}:用来给未定义的变量设置默认值

      ###### (注意：当且仅当param未定义时会以default值代替，param自始至终仍是未定义状态！):

      ```bash
      #!/bin/bash
      unset foo
      echo "\$foo = ${foo:-bar}"	#foo未定义状态，此时输出为： $foo = bar
      foo=bbb
      echo "\$foo = ${foo:-bar}"	#foo已被定义且赋值，此时该条语句不成立不会执行后面的-bar，此时输出： $foo = bbb
      ```

      

    - ###### ${param#word}:从头开始匹配，删除与word匹配的最小部分，剩余的param子串全部输出

      ```bash
      #!/bin/bash
      foo=/usr/include/x11/linux/shell
      echo ${foo#*/}	#输出 usr/include/x11/linux/shell，第一个匹配 */的子串为第一个/,除了这个字符串其余全部保留
      exit 0 
      ```

      

    - ###### ${param##word}:从头开始匹配，删除与word匹配的最长部分的子串，其余子串全部输出

      ```bash
      #!/bin/bash
      foo=usr/include/x11/linux/shell
      echo ${foo##*/}		#输出： shell，匹配的最后一个*/的子串为usr/include/x11/linux/,剩余子串:shell全部保留
      exit 0
      ```

      

    - ###### ${param%word}:从尾部开始，删除与word匹配的最少部分，其余全部输出

      ```bash
      #!/bin/bash
      foo=/usr/linux/include/x11/linux/shell
      echo ${foo%/linux*}	#输出： /usr/linux/include/x11,%为从尾部向前找到与word匹配最短的部分进行删除，剩余保留
      exit 0
      ```

      

    - ###### ${param%%word}:从尾部开始，删除与word匹配的最长部分，其余全部输出

      ```bash
      #!/bin/bash
      foo=/usr/linux/include/x11/linux/shell
      echo ${foo%%/linux*}	#输出： /usr ，删除最长与 /linux* 匹配的子串，剩余全部输出
      ```

      

82. ##### 清空文件内容：

    ```bash
    cat /dev/null > a.out	#清空a.out,不会修改源文件的属性。
    ```

    

83. ##### here文档：

    ###### 允许一条命令通过重定向方式像读取文件或者键盘输入似的从一个文本段获取内容here.sh:

    ```bash
    #!/bin/bash
    cat << !HAHAHA!	#here文档以重定向符号 << 开始，后面紧跟的与末尾相同的 !HAHAHA!为here文档的标识符，用来标识here文档的起始位置。
            这是从here指令输入的一段语句。
            该指令以'!HAHAHA!'为标识符，分别出现在起始位置
            标识文本的起始位置。
            最后使用重定向 << 输出给cat指令，作为cat的输入
    !HAHAHA!
    ```

    ###### ./here.sh输出结果:

    ```bash
            这是从here指令输入的一段语句。
            该指令以'!HAHAHA!'为标识符，分别出现在起始位置
            标识文本的起始位置。
            最后使用重定向 << 输出给cat指令，作为cat的输入
    ```

    

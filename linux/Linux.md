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

39. 




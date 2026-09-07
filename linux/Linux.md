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

22. 


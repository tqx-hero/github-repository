1. 编译c/c++文件时必须带上-g调试参数：

   ```shell
   gcc[g++] -g a.c[a.cpp] -o a
   ```

   

2. 启动debug模式：

   ```shell
   gdb ./a
   ```

   

3. 设置运行参数：

   ```shell
   #相当于在main函数入口键入参数
   set args [param1,param2,...]
   ```

   

4. 显示设置的运行参数：

   ```shell
   show args 
   ```

   

5. 开始调试：

   ```shell
   #如果没有设置断点，会直接运行到出错的那一行，没有错误会直接运行结束
   r(或者run)
   #开始运行，仅运行一行
   start
   ```

   

6. 设置断点：

   ```shell
   #在源码第10行打断点
   break(或简写b) 10
   #在file.c文件的第100行设置断点
   break file.c:100 
   #在函数func处设置断点
   b func
   #查询所有断点信息
   i b (或者info b、info break等)
   
   break main.c:10       # 在main.c的第10行设置断点
   break function_name   # 在函数入口设置断点
   break *0x8048000      # 在内存地址设置断点
    
   info breakpoints      # 查看所有断点
   delete 2              # 删除编号为2的断点
   disable 1             # 禁用编号为1的断点
   enable 1              # 启用编号为1的断点
    
   # 条件断点
   break 15 if x == 5    # 当x等于5时在第15行中断
   
   #使2号断点失效。（号码为上面断点列表中的号码Num）
   disable break(b也可以) 2
   #使2号断点有效。
   enable break(b也可以) 2
   #删除2号断点
   delete break 2
   #针对所有断点操作：
   disable[enable/delete] breakpoints
   ```

7. 查看断点、display的信息：

   ```bash
   info break[display]
   i b[display]
   ```

8. 设置到达断点后要执行的指令：

   ```bash
   #设置2号断点(号码为断点列表中的Num)
   (gdb) commands 2
   
   Type commands for breakpoint(s) 2, one per line.
   End with a line saying just "end".
   >display num	#设置到达2号断点后屏幕显示num的值
   >end	#end代表键入命令结束
   ```

   

9. list的用法：

   ```shell
   #显示第20行上下几行的内容
   list 20
   #显示main函数上下几行的内容
   list main
   #显示当前行下面的几行内容
   list 
   #显示当前行上面几行内容
   list - 
   ```

   

10. 逐步往下走：

   ```shell
   next(或者n)
   step(简写为s可进入函数内部)
   continue(简写c，直接跳转到下一个断点)
   ```

   

11. 显示某一个变量的值：

    ```shell
    #持续显示abc的值
    display abc
    #去掉第2项的display展示项
    disable display 2
    #print指令是输出abc的值，只输出一次，不会钉在屏幕上
    print abc
    
    print x               # 打印变量x的值
    print/x x             # 以十六进制打印x
    print array[10]@5     # 打印数组从第10个元素开始的5个元素
    print *(int*)0x1234   # 打印内存地址0x1234处的整数值
     
    set var x = 10        # 修改变量x的值为10
    set {int}0x1234 = 10  # 修改内存地址0x1234处的值为10
    ```

    

12. 退出调试：

    ```gdb
    quit(q)
    ```

13. 选择调试的进程(`fork(2)` 后的父子进程间切换)：

    ```bash
    #选择调试子进程
    (gdb) set follow-fork-mode child
    #选择调试父进程
    (gdb) set follow-fork-mode parent
    ```

    

14. 调试线程：

    ###### 在线程2上设置断点：

    ```bash
    (gdb) b file.c:20 thread 2
    ```

    ###### 查看当前程序的所有线程：

    ```bash
    #会以列表形式展示程序的所有线程，gdb会给每个线程分配Id，Id前面带 * 的是当前调试的线程
    (gdb) info threads
    ```

    ###### 调试目标ID指定的线程：

    ```bash
    (gdb) thread 3 #调试Id为3的线程
    ```

    ###### 设置是否锁定其他线程：

    ```bash
    #off: 不锁定，即所有线程同时执行。
    #on: 只有当前调试的线程执行
    #step：只有单步执行时，只有当前线程执行
    (gdb) set scheduler-locking [off | on | step | reply]
    ```

    

15. 观察点（Watchpoints）：

    ```bash
    watch x               # 当x被修改时中断
    rwatch x              # 当x被读取时中断
    awatch x              # 当x被读取或修改时中断
    info watchpoints      # 查看所有观察点
    ```

16. 调用栈分析：

    ```bash
    backtrace             # 显示调用栈
    backtrace full        # 显示调用栈及局部变量
    frame 2               # 切换到栈帧2
    info frame            # 显示当前栈帧信息
    info args             # 显示当前函数的参数
    info locals           # 显示当前函数的局部变量
    ```

17. 处理信号：

    ```shell
    info signals         # 查看信号处理方式
    handle SIGSEGV stop  # 当收到SIGSEGV时中断
    handle SIGINT print  # 当收到SIGINT时打印信息
    ```

18. 






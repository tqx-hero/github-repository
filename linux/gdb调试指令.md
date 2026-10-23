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
   #在函数func处设置断点
   b func
   #查询所有断点信息
   i b (或者info b、info break等)
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
    ```

    

12. 退出调试：

    ```gdb
    quit(q)
    ```

    

13. 栈跟踪：

    ```c
    backtrace (简写bt)或者where
    ```

    该指令可跟踪该函数是由哪个函数调用过来的。

14. 
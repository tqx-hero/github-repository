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
   ```

   

7. list的用法：

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

   

8. 逐步往下走：

   ```shell
   next(或者n)
   step(简写为s可进入函数内部)
   ```

   

9. 显示某一个变量的值：

   ```shell
   #显示abc的值
   display abc
   ```

   

10. 
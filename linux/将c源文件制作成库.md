1. 将所要制作的库.c，编译成.o文件(单独编译)：

   ```shell
   gcc -c a.c -fpic -o a.o (-fpic是让库共享)
   ```

   

2. 将相关的.o文件打包成静态库mymath：

   ```shell
   #库名称以lib*开头，后面追加要打包成库的所有目标文件
   ar -rcs libmymath.a *.o 
   ```

   

3. 在程序中使用库mymath.a/mymath.so：

   ```shell
   #1、先引入头文件mymath.h
   #使用gcc编译命令进行编译
   gcc test.c -o test -L ./ -lmymath -I ./
   ########
   -L:大写L，用来指明库文件所在路径。如果将库文件放到/lib或/usr/lib/,可以不指定，编译器默认从这两个路径下查找。
   -l:小写L，用来指明需要链接库的库名。注意：库文件.a名称包含lib前缀，在这里不需要指明这个前缀。而且库名必须显式指明。
   -I:大写i，用来指明头文件所在路径。如果将头文件放到/usr/include/下或者与程序在同一个路径下，可不需要显式声明。
   ```

   

4. 将相关的.o文件打包成动态库dymath:

   ```shell
   gcc -shared *.o -o libdymath.so
   ```

   

5. 配置动态链接库的ld配置文件，添加一条动态链接库文件的绝对路径：

   ```shell
   #1、打开配置文件
   sudo vim /etc/ld.so.conf
   #2、在其中另起一行添加so文件所在绝对路径：
   #3、使配置立即生效，重新加载链接库
   sudo ldconfig -v
   ```

   

6. 
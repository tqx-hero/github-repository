1. 下载boa源码包：boa*.tar.gz。

2. 解压安装包：

   ```bash
   tar -zxvf boa*.tar.gz [-C 选择安装目录]
   ```

   

3. 安装依赖：

   ```bash
   sudo apt install flex bison
   ```

   

4. 进入src目录生成makefile文件：

   ```bash
   ./configure
   ```

   

5. 执行makefile：

   ```bash
   make
   ```

   

6. 修改compat.h:120行:

   ```c
   #define TIMEZONE_OFFSET(foo) foo##->...    //将##删除，参数是一个指针，不能使用##进行字面量拼接
   //重新编译：
   make clean && make
   ```

   

7. 修改配置文件defines.h(30行):

   ```c
   #define SERVER_ROOT "/etc/boa"   
   //将服务器的根目录设置成boa可执行文件所在的文件夹,如将其设置为/home/tqx/boa/boa
   #define SERVER_ROOT "/home/tqx/boa/boa"  
   ```

   

8. 重新编译一下，生成新的boa可执行程序：

   ```bash
   make clean && make
   ```

   

9. 创建三个文件夹，用于boa.conf中的配置项：

   ```bash
   cd /home/tqx/		#进入目录
   mkdir boa && cd boa	#创建boa的总文件夹并进入
   mkdir boa log www	#创建三个文件夹boa/log/www。boa用于存放boa服务与配置文件；log存放日志文件；www用于存放静态html
   ```

   

10. 将生成的boa可执行文件与配置文件boa.conf复制到步骤7设置的服务器根路径：

    ```bash
    cp boa /home/tqx/boa/boa
    cp ../boa.conf /home/tqx/boa/boa
    ```

    

11. 将静态界面放入/home/tqx/boa/www目录下，必须包括index.html

12. 配置boa.conf:

    ```shell
    #设置存储boa日志文件
    #accesslog存放位置与错误文件存放位置：
    74 AccessLog /home/tqx/boa/log/access_log
     62 ErrorLog /home/tqx/boa/log/error_log
     #为此需要再在上面的boa总目录下创建2个文件(是文件不是文件夹)
    touch /home/tqx/boa/log/access_log /home/tqx/boa/log/error_log
    
     48 User 0	#设置用户，不设置写0
     49 Group 0 #设置用户组，不设置写0
    	#在www目录下创建cgi-bin文件夹
    mkdir /home/tqx/boa/www/cgi-bin
    #在第193行设置cgi-bin目录为/home/tqx/boa/www/cgi-bin/
    ```

    ![image-20260828142351369](C:\Users\田庆新\AppData\Roaming\Typora\typora-user-images\image-20260828142351369.png)

    ![image-20260828142458041](C:\Users\田庆新\AppData\Roaming\Typora\typora-user-images\image-20260828142458041.png)

    ![image-20260828143228372](C:\Users\田庆新\AppData\Roaming\Typora\typora-user-images\image-20260828143228372.png)

    

    

13. 端口号问题：

    ```c
    //boa.conf中的端口号默认为80，端口为熟知端口号，即小于1024，必须使用root权限，否则内核报错拒绝访问。
    //可根据需要设置大于1024的端口号，比如8080/8090等，省去权限的麻烦.
    ```

    

14. 到服务器所在目录下启动服务：

    ```bash
    ./home/tqx/boa/boa/boa
    ```

    

15. 
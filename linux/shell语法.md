1. 声明执行脚本的程序：

   ```bash
   #声明bash程序执行该脚本
   #!/bin/bash
   #声明sh程序执行
   #!/bin/sh
   ```

   

2. 脚本执行方式：

   ```bash
   #fork新的子进程执行脚本：
   bash test_bash
   ./test_bash
   #当前进程执行脚本：
   . test_bash
   source test_bash
   ```

   

3. 自定义变量(字符串)：

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

   

4. 从标准输入读取字符串赋值给变量name(scanf的作用)：

   ```bash
   read name	#scanf的作用，从终端获取输入的字符串，赋值给name
   
   tqx@linux-ubuntu:~$ read name
   tqx
   tqx@linux-ubuntu:~$ echo $name
   tqx
   ```

   

5. 设置变量为常量：

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

   

6. 声明整型变量：

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

   

7. 输出字符串的子串、长度：

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

8. 查看环境变量：

   ```bash
   env	#列出所有的环境变量
   export name="str"	#将name设置到当前进程的环境变量中。该变量可以被fork子进程继承
   export -p #列出所有环境变量中的参数值
   export -n [name] #删除名称为name的环境变量。
   #注意：如果使用脚本在当前进程设置环境变量，执行命令必须使用: . 或者source ，使其在当前进程执行。如果使用bash或者./执行
   #会开启新的子进程执行，当前进程作为父进程不会有任何改变。
   #以上指令只会在当前进程存活时有效，持久化就需要写入~/.bashrc（登录用户有效），或者/etc/profile(全局有效),当用户登录开启shell进程时会自动调用这几个脚本文件
   ```

9. 脚本内获取参数：

   ```bash
   $#	#获取参数的个数
   $*	#获取参数列表(省去了第一个参数，也就是执行脚本的命令)
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
   ```

   

10. 特殊符号：

    ```bash
    #指令：``用于执行内部指令，等同于$()
    `date`
    $(pwd)
    #$name:用于获取变量name的值
    echo $name
    #"":弱引用类型，被包裹的字符串中使用特殊字符可以被解析
    echo "$name"	#可以被解释成取name的值
    # '':强引用类型，只会把内容当成字符串输出
    echo '$name' #输出$name
    # ( 内容 )：fork子进程去执行括号内的脚本
    # { 内容; }:当前进程执行该脚本
    ```

    DEMO：

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

    

11. 测试文件存不存在：

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

    

12. 
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

   

10. 特殊符号：

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

    

12. 逻辑运算符&&、||、！：

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

    

13. 条件运算符：

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
      
      

14. 循环语句：

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

      

15. 函数的使用：

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
    
    
    
16. 算术运算：

    ```bash
    $(( exp ))	#可以在exp中执行算术运算，并且结果可输出、可赋值
    tqx@linux-ubuntu:~/linux-learn/shell/function$ echo "$(( 1+2 ))"
    3
    tqx@linux-ubuntu:~/linux-learn/shell/function$ ret=$(( 3+10 )) && echo "$ret"
    13
    ```

    

17. 条件判断：

    ```bash
    (( exp ))	#仅仅判断表达式的算术运算的真假，仅返回$?
    # (( 10 > 20 ))结果为假，$?不为0，会执行else分支，输出第二个echo
    tqx@linux-ubuntu:~/linux-learn/shell/function$ if (( 10 > 20 ));then echo "10 > 20 ";else echo "10 < 20";fi
    10 < 20
    ```

    

18. test测试：

    ```bash
    [ exp ]		#等价于 test exp，是test的更简洁可读的写法
    #条件测试 10 不等于20，为真返回第一个echo
    tqx@linux-ubuntu:~/linux-learn/shell/function$ [ 10 -ne 20 ] && echo "10 != 20" || echo "10 ==20"
    10 != 20
    ```

    

19. 空命令：

    ```bash
    :	#空命令，在条件判断里面可以当做true的简化写法，因为是内置命令，处理起来比true要快，但可读性差，while : 等价于while true
    #: = true,什么也不输出
    tqx@linux-ubuntu:~/linux-learn/shell/function$ [ 10 -ne 20 ] && : || echo "10 ==20"
    tqx@linux-ubuntu:~/linux-learn/shell/function$
    ```

    

20. eval:

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

    

21. 
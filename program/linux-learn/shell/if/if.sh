#!/bin/bash
#if表达式的基础用法
###############文件测试########################
if [ -f /bin/bash ]
then 
	echo "文件： /bin/bash存在"
fi

if [ -d /bin/bash ]
then 
	echo "文件是个目录"
else
	echo "文件不是目录"

fi

if [ -f ./if.sh ]
then
	echo "if.sh存在，并且是一个普通文件"
else 
	echo "if.sh不是普通文件"
fi

if [ -e ./test-file ]

then 
	if [ -d ./test-file ]
	then
		echo "test-file存在，并且是一个目录"
	fi
else 
	echo "test-file不存在"
fi

###################字符串测试########################

username=www

if [ -n $username ] 
then 
	echo "\$username不为空，值= $username"
else
	echo '$username为空'
fi

unset username

if [ -z $username ]
then 
	echo username为空
else 
	echo "username = $username"
fi

#user=www
#username=www
echo "请输入username："
read username
echo "请输入user:"
read user
echo "相等判断结果："
if [ $user = $username ]
then
	echo "user = username"
else 
	echo "user != username"
fi
echo "不相等判断结果："

if [ $user != $username ]
then 
	echo "user != username"
else 
	echo "user = username"
fi

exit 0

#!/bin/bash
#测试逻辑运算符： && ||

echo "请输入用户名user:"
read user

if [ -n "$user"  ] && [ "$user" = "tqx" ]; then

echo "用户名=$user"

elif [ "$user" != "root" ]; then
	echo "您无权访问"
	exit 1
else 
	echo "用户名$user"

fi

exit 0


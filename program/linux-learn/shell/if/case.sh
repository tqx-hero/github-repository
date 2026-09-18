#!/bin/bash

#case语句使用
echo "现在是早上吗？请输入yes/no"
read config
case "$config" in

'yes' | 'y' )	echo "您输入的是yes";;
'no' | 'n' )	echo "您输入的是no";;
* )	echo "输入不合法";;

esac

exit 0

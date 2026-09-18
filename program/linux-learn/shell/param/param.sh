#!/bin/bash
echo $#
echo $*
echo $?
echo "以下是参数列表"
echo $0
echo $1
echo $$
echo "$@"
echo "下面是对参数列表的遍历..."
for param in "$@";do
	echo "$param"
done
exit 0

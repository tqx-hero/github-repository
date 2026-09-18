#!/bin/bash

function sum_all(){
	if [ $# -ne 1 ]; then
		echo "请输入参数"
		return 1;
	elif [ $1 -lt 0 ] || [ $1 -gt 100 ];then
		echo "请输入0~100内的数字"
		return 1;
	fi
	declare -i sum=0
	for ((i=0;i <= $1;i+=1));do
		sum+=i;	
	done
	echo "$sum"
	return 0
}

declare -i n1
echo "请输入要累加的数"
read n1
sum_all $n1
ret=$(sum_all $n1)
echo "结果= $ret"


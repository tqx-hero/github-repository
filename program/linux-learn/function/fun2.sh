#!/bin/bash

function add(){
	if [ $# -ne 2 ];then 
		echo "参数个数不正确"
		return 1;
	elif [ $1  -gt 1000 ] || [ $2 -gt 1000 ] ;then
		echo "请输入不超过1000的正整数"
		return 1;
	fi
	echo "add() n1 = $1"
	echo "add() n2 = $2"
	local sum=$(($1+$2))
	echo "add() sum = $sum"
	return 0;
}

declare -i n1 n2
echo "请输入2个要相加的数字"
read n1 n2
ret=$(add $n1 $n2)
echo "$n1+$n2 = $ret"

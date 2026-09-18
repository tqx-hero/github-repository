#!/bin/bash

#表达式条件判断用法

if [ 10 -gt 20 ]
then 
	echo "10 > 20"
else 
	echo "10 < 20"
fi

declare -i n1=10+20
declare -i n2=20+10

if [ $n1 -gt $n2 ]; then
	echo "10+20 > 20+10"
elif [ $n1 -lt $n2 ]; then 
	echo "10+20 < 20+10"
elif [ $n1 -eq $n2 ]; then 
	echo "10+20 = 20+10"
else
	echo "error"
	exit 1
fi

exit 0 

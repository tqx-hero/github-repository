#!/bin/bash
#while循环用法
declare -i sum=0
declare -i i=0

while [ "$i" -le  100 ]; do
	sum+=i
	i+=1
done
echo "sum = $sum"
exit 0

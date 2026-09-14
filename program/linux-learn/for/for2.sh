#!/bin/bash
#for循环第二种方式，迭代一定次数

declare -i sum

for ((i=0;i<100;i=i+1)); do

	sum=$sum+i
done
echo "sum = $sum"
exit 0

#!/bin/bash
#until循环使用，与while循环相反，当满足条件时跳出循环

declare -i sum=0
declare -i i=1

until [ "$i" -gt 100 ]; do

	sum+=i
	i+=1
done
echo "sum =$sum"
exit 0

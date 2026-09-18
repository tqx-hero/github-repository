#!/bin/bash
#数组的定义，使用
array=("abc" "cbd" "efg" "ghi")
array+=("jkl")

echo "下面是直接迭代获取数组元素"
for item in "${array[@]}" ;do
	echo "$item"
done

echo "下面是用下标访问的遍历"
declare -i i=0
for i in "${!array[@]}" ; do
	echo "第i个元素值 = ${array[$i]}"
	i+=1
done
unset array
exit 0

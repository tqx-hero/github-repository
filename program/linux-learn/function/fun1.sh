#!/bin/bash
#函数的简单用法

function is_dir(){
	if [ $# -lt 1 ]; then
		echo "参数个数不足"
		return 1;
	elif [ ! -d $1 ];then
		echo "不是一个目录"
		return 2;
	else
		return 0;
	fi
}

echo "请输入你要查询的目录路径:"
read dir

is_dir $dir
echo "$dir 查询结果= $?"


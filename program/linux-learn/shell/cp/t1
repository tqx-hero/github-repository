#!/bin/bash
# trap的使用

file_name=`date +%F`-$$.log
declare config=1
#设置中断信号处理
#trap "rm -rf $file_name" INT
trap config=0 INT
echo "正在创建测试文件 : $file_name"
touch $file_name
echo "文件创建成功"

while [ -f $file_name ] && [ $config -gt 0 ] ;do
	echo "文件存在，循环中...\n"
	ls >> $file_name
	sleep 1
done

echo "第一个中断处理程序执行完毕"

#command 为空表示忽略某个信号，不进行捕获，即进行默认的处理
trap INT
while : ;do
	echo "正在进行第二个循环..."
	sleep 1
done

echo "程序退出"


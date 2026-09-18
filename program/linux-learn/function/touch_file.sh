#!/bin/bash

function touch_file(){
	cd "/home/tqx/test/"
	declare -i i=3
	until [ $i -eq 0 ];do
		echo "请输入要创建的文件名,你还有[$i]次机会:"
		read file_name
		if [ -f "$file_name" ];then
			i=i-1
			if [ $i -gt 0 ];then
				echo "文件已存在，请重新输入"
			fi
		else
			touch $file_name
			break;
		fi
	done
	case $i in 
	3 | 2 | 1 ) echo "文件:$file_name 创建完毕";;
	* ) echo "次数已使用完毕，正在退出";;
	esac
}

if [ -d "/home/tqx/test" ];then
	touch_file
else
	echo "按y创建，按n退出"
	read config
	case "$config" in 
	'y' | 'Y' | 'YES' | 'yes' ) 
		mkdir -p "/home/tqx/test"
		echo "已创建test文件夹"
	;;
	'n' | 'N' | 'no' | 'NO' ) 
		echo "正在退出..."
	;;
	esac
fi

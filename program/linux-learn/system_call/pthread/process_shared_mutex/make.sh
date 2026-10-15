#!/bin/bash

# 删除旧的二进制文件
find . \( -type f ! -name "*.*" \) -exec rm -rf {} +

src=("main_process" "thread_print")
liblink=-lpthread
for item in "${src[@]}";do
	#echo "$item"
	gcc "$item".c -o "$item" $liblink
done

./"${src[0]}"

#1/bin/bash
# 生成聊天程序的脚本
src="three_chat_define.c"
names=("Join" "Bob" "Lucy");
find . -name "*_chat" -type f -exec rm -rf {} + 
for item in "${names[@]}";do
	gcc -g $src -D${item:0:1} -o ${item}_chat 
	echo "已生成可执行程序: ${item}_chat"
done

writer=("Bob" "Lucy" "John")
src="./three_chat.c"

find . -name "*_chat" -type f -exec rm -rf {} + 

for item in ${writer[@]};do
	gcc "${src}" -o "${item}"_chat -lpthread -D"${item:0:1}"
	echo "已生成可执行程序: ${item}_chat"
done

ls 

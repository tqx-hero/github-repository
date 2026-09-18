#!/bin/bash
#for循环
array=(foo,bar,fu,mm)
for fn in $array; do 
	echo $fn
done
path=/home/tqx/
for file in $(ls "$path"*); do
	[ -e "$file" ] || continue 
	if [ -f "$file" ]; then 
		echo "$file is file"
	elif [ -d "$file" ];then
		echo "$file is dir"
	else 
		echo "^_^"
	fi

done

exit 0

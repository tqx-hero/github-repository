#!/bin/bash
#for循环
array=(foo,bar,fu,mm)
for fn in $array; do 
	echo $fn
done

for file in $(ls ../if/*.sh); do
	echo $file
done

exit 0

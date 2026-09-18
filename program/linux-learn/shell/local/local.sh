#!/bin/bash
sample_text="这是一个全局测试变量"

foo(){
	local sample_text="这是函数体内部的局部变量"
	echo "函数体内部：$sample_text"
}

echo "进入函数之前：$sample_text"

foo

echo "函数调用之后：$sample_text"
exit 0

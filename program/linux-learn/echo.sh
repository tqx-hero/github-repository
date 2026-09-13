#!/bin/bash
echo "测试source与.命令，执行sh文件"

echo "HOME =  $HOME"
echo "今天 = `date`"
echo "当前目录= $(pwd)"

name=student
( name="张三" 
echo "子进程1= $name" )
( echo "子进程2 = $name" )
echo "当前进程 = $name"
{ name="李四";echo "当前进程{} = $name"; }
echo "当前进程2 = $name"

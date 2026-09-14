#!/bin/bash
#引号的使用

myparam=大家好才是真的好
echo 不带引号的= $myparam
echo "双引号的=$myparam"
echo '单引号的=$myparam'
echo "带转义字符\\的：\$myparam"
echo 请输入要修改的变量值:
read myparam
echo '当前myparam的变量值=' "$myparam"
exit 0;

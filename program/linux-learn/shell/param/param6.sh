#!/bin/bash
unset foo
echo "初始化之前 \$foo = $foo"
echo "初始化时，\$foo =  ${foo:-bar}"
foo=bbb
echo "初始化之后 \$foo = ${foo:-bar}"
exit 0

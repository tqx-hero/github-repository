一、先写一个最简单的 C 程序
test.c
c
运行
#include <stdio.h>

int main() {
    int a = 10;
    int b = 3;
    int c = a + b;
    printf("c = %d\n", c);
    return 0;
}
二、编译时必须加 -g（生成调试信息）
bash
运行
gcc -g test.c -o test
-g 最重要，没有它 gdb 无法调试。
三、启动 gdb
bash
运行
gdb ./test
进入 gdb 界面。
四、最常用的 10 个 gdb 命令（背会就够用）
1. 查看代码
plaintext
l
list 的缩写，显示源代码。
2. 设置断点（最常用）
plaintext
b 行号
例如：
plaintext
b 6
b main
3. 运行程序
plaintext
r
run，跑到断点停下。
4. 单步执行（不进入函数）
plaintext
n
next，一步一步走。
5. 单步执行（进入函数）
plaintext
s
step，会进入 printf 这种函数。
6. 查看变量
plaintext
p 变量名
plaintext
p a
p c
7. 继续运行到下一个断点
plaintext
c
continue
8. 退出 gdb
plaintext
q
9. 查看当前断点
plaintext
info b
10. 删除断点
plaintext
d 断点号
五、超级重要：查看汇编 + 寄存器（你学 x86 必用）
gdb 可以直接看 x86 汇编指令 和 寄存器值！
查看汇编指令
plaintext
disassemble main
单步执行汇编（一条指令一条指令走）
plaintext
si
查看所有寄存器（eax、ebx、esp、eip...）
plaintext
info registers
或者简写：
plaintext
i r
只看某个寄存器
plaintext
i r eax
i r ebx
六、最爽的调试布局（一边看代码一边看汇编）
plaintext
layout src
看 C 代码
plaintext
layout asm
看汇编指令
plaintext
layout regs
同时看：代码 + 汇编 + 寄存器
（你学 x86 最有用的命令）
七、完整演示流程
plaintext
gdb ./test
b 6        # 断点在第6行
r          # 运行
n          # 单步
p c        # 看变量
si         # 单步执行汇编
i r        # 看寄存器
layout asm # 看汇编
c          # 继续
q          # 退出
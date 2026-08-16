#include <stdio.h>

int add(int a,int b){ return a+b; }
int sub(int a,int b){ return a-b; }
int mul(int a,int b){ return a*b; }

// 函数指针数组
int (*funcs[])(int,int) = {add, sub, mul};

extern void asm_call_all(int (**func_arr)(int,int), int len, int a, int b);

int main(){
    // 批量调用 add、sub、mul
    asm_call_all(funcs, 3, 10, 2);
    return 0;
}
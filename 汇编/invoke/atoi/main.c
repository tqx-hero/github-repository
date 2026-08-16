//
// Created by Administrator on 2026/6/9.
//
#include <stdio.h>
extern int asm_atoi(const char *s);

int main(){
    printf("%d\n", asm_atoi("1234"));  // 1234
    printf("%d\n", asm_atoi("987abc"));// 987
    printf("%d\n", asm_atoi("0"));     // 0
    return 0;
}
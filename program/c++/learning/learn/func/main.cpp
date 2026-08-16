//
// Created by Administrator on 2026/7/9.
//
//或者直接将这个main函数用到的所有外部函数全部放到.h头文件内，导入头文件，编译时会自动把头文件中声明的函数一起编译
#include "main.h"
// void print_str(string str);
//只需要声明函数，在编译这个文件时连同函数所在的文件一块编译即可，链接阶段会自动进行链接
// void pt(string str);
// int main() {
//     string str = "hello";
//     // print_str(str);
//     pt(str);
//     return 0;
// }

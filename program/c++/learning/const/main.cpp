#include <cstdio>
//
// Created by Administrator on 2026/7/3.
//
// int main() {
//     const int a = 10;
//     // int *p = &a; //int * 类型的指针不能指向const声明的变量，因为会导致所指向的常量修改,只能使用const in *指针来表示对象不允许修改
//     const int *pp = &a; //这样是可以的，const 锁的是*pp，即指针pp解引用的对象，表示该对象不允许修改，符合a的常量语义，编译期通过
//
//     const char * s1 = "hello world";
//     const char * s2 = "hello world";
//     printf("s1 = %p\n",s1);
//     printf("s2 = %p\n",s2);
//     return 0;
// }

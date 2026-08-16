//
// Created by Administrator on 2026/7/5.
//

#include <iostream>
//声明的外部常量必须在声明时使用extern使其具有外部链接属性，否则默认是内部连接属性(作用域与static相同)
//外部声明无法链接
//所以如果定义的常量只想使其作用在本文件，直接使用const即可
//否则使用extern恢复其外部链接属性
extern const int const_number = 100;

class A {
public:
    void set(int i) { num = i; }
    void get() { std::cout << "i = " << num << std::endl; }

private:
    static int num;
};

//使用之前需要声明，表示后面的函数内部引用A类内部的静态成员变量num
//告诉编译器与链接器变量的位置
int A::num;

// int main() {
//     A a, b;
//     a.set(20);
//     b.get();
//     return 0;
// }

//
// Created by Administrator on 2026/7/9.
//
#include <iostream>
using namespace std;
//const修饰指针指向的常量可以重载
void func(int *p) {
}

//传入的参数指向的是常量时调用该函数
void func(const int *p) {
}

//const修饰的引用如果是常量也可以进行重载
void func(int &p) {
}

//传入的参数为常量时调用该函数，可以重载
void func(const int &p) {
}

void fc(const int &x) {
    cout << x << endl;
}

void f(short x) {
    cout << "short" << endl;
}

void f(float x) {
    cout << "float" << endl;
}

void f(double x) {
    cout << "double" << endl;
}

// int main() {
//     //如果传入的是一个常量，会调用形参为const引用的那个函数
//     fc(2);
//     //如果使用浮点数传入，会进行隐式类型转换，即小数点全部截断，把浮点数转化为整型进行传参
//     fc(2.2f);
//     //只要可以进行类型转换，这里的浮点数调用后转换成了short类型，可以进行类型转换，就可以使用
//     f(2.3f);
//
//     return 0;
// }

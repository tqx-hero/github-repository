#include <iostream>
//
// Created by Administrator on 2026/7/4.
//
class A {
    long long num;

public:
    A() : num(10) {
    }

    virtual void f() { std::cout << "A:f()  " << num << std::endl; }
};

class B : public A {
    long long num;

public:
    B() : num(20) {
    }

    virtual void f() { std::cout << "B:f()  " << num << std::endl; }
};

// int main() {
//     // A a;
//     // B b;
//     // // a.f();
//     // // b.f();
//     //
//     // A* aa = &b;
//     // aa->f();    //调用的B函数
//     //
//     // // a=b;    //这个只是一个简单的赋值操作，不会牵扯虚表的转换
//     // // a.f();
//     // // A& aaa = b;
//     // // aaa.f();
//     return 0;
// }

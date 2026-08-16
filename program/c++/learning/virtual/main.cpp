#include <iostream>
//
// Created by Administrator on 2026/7/4.
//
class A {
public:
    long long i;

    A() : i(10) {
    }

    virtual long long get() { return i; }
};

class B {
public:
    long long i;
};

// int main() {
//     // A a, b;
//     // long long *aa = (long long *) &a;
//     // long long *bb = (long long *) &b;
//     // std::cout << " size  = " << sizeof(a) << std::endl;
//     // std::cout << " i  = " << a.i << std::endl;
//     // std::cout << " aa = " << (*aa) << std::endl << " bb = " << (*bb) << std::endl;
//     // aa++; //由于用的是64位开发环境，指针大小为8字节，所以需要往后偏移8个字节
//     // std::cout << " i  = " << (*aa) << std::endl;
//     B b;
//     std::cout << "size  = " << sizeof(b) << std::endl;
//     return 0;
// }

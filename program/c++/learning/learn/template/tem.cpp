//
// Created by Administrator on 2026/7/16.
//
#include <iostream>

template<typename T> //声明后面的第一个函数是模板函数，T为模板类
// template<class  T>
void mySwap(T &x, T &y) {
    T temp = x;
    x = y;
    y = temp;
}

void test01() {
    int a = 10, b = 20;
    mySwap(a, b);
    std::cout << "a = " << a << std::endl;
    std::cout << "b = " << b << std::endl;
}

void test02() {
    using std::cout;
    using std::endl;
    double a = 3.14f, b = 8.88f;
    mySwap(a, b);
    cout << "a = " << a << endl;
    cout << "b = " << b << endl;
}

void test03() {
    float a = 10.0f, b = 20.1f;
    mySwap(a, b);
    std::cout << "a = " << a << std::endl;
    std::cout << "b = " << b << std::endl;
}

// int main() {
//     test01();
//     test02();
//     return 0;
// }

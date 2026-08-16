//
// Created by Administrator on 2026/7/11.
//
#include <iostream>
using namespace std;

int mul(int x, int y) {
    return x * y;
}

class A {
    int num;

    typedef int (func)(int, int);

public:
    explicit A(int num)
        : num(num) {
    }
    //重载()，伪函数来实现动态绑定函数
    int operator()(int x, func *fc) {
        return fc(num, x);
    }

};

// int main() {
//     A a(20);
//     int val = a(10, mul);
//     cout << val << endl;
//     return 0;
// }

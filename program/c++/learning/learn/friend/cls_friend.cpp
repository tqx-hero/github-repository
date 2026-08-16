//
// Created by Administrator on 2026/7/11.
//

#include <iostream>
using namespace std;

//友元函数不能被继承、单向、也没有传递性
class A {
    friend class B;
    friend class Number;
    int num;

public:
    explicit A(int num)
        : num(num) {
    }
};

class B {
public:
    void print(A &a) {
        cout << a.num << endl;
    }
};

// int main() {
//     B b;
//     A a{30};
//     b.print(a);
//     return 0;
// }

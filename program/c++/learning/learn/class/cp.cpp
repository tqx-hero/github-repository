//
// Created by Administrator on 2026/7/10.
//
#include <iostream>
using namespace std;

class Test {
    int num;

public:
    int get_num() { return this->num; }

    Test() : num(10) {
    }

    explicit Test(int num)
        : num(num) {
    }

    Test(const Test &other)
        : num(other.num) {
        cout << "拷贝构造被调用" << endl;
    }

    Test &operator=(const Test &other) {
        this->num = other.num + 10;
        cout << "重载操作符=被调用" << endl;
        return *this;
    }
};

// int main() {
//     Test ts;
//     //类初始化时会有一个默认的拷贝构造
//     Test tts(ts), tss(30);
//     //拷贝构造只在对象初始化时被调用，像这种属于直接赋值
//     //调用的其实是类的重载操作符=。如果没有重载操作符，编译器会调用默认的操作符
//     tss = tts;
//     // cout << tts.get_num() << endl;
//     cout << tss.get_num() << endl;
//     return 0;
// }

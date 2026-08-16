#include <iostream>
#include <string>
//
// Created by Administrator on 2026/7/5.
//
using namespace std;
//深拷贝与浅拷贝

class A {
public:
    string name;
    int number;

    A() : name(""), number(10) {
    };

    A(const string &name, int number)
        : name(name),
          number(number) {
    }

    A(const A &a) : name(a.name), number(a.number) {
    }

    virtual ~A() {
    }
};


// int main() {
//     //执行该赋值操作，编译器会运行默认的拷贝构造函数，即A(const A& a): name(a.name),number(a.number){}
//     //但注意，字符串string与c中的一样都属于常量，string name其实是char*，指向字符串的指针
//     //此时执行该构造函数时，拷贝的内容实际上是指针的拷贝
//     //结果a与b的name指针指向了同一个字符串内存
//     //在main函数执行完成之前会对a、b调用析构函数，析构函数会释放内存空间。
//     //在释放name指针时，比如a先完成释放free，接着b再对这个指针进行释放，但是name指针已经被释放了，同一个指针2次释放必然会导致系统崩溃
//     string name = "张三";
//     A b = {name, 20};
//     A a = b;
//     cout << a.name << endl;
//     return 0;
// }

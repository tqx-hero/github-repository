//
// Created by Administrator on 2026/7/21.
//
#include <iostream>
using namespace std;

namespace vir {
    class Parent {
        int num;

    public:
        virtual void show() {
        }

        virtual ~Parent() {
        }
    };

    //只要子类继承了父类
    //父类中存在虚函数
    //无论子类是否重写了该虚函数，或者有没有声明虚函数，子类对象都会创建一份额外的虚表
    //对象中除了包含父类的结构(父类的所有成员变量与虚表指针vptr)，还会额外增加一个long类型的虚表指针vptr
    //当然每个对象都需要内存对齐。
    class Child : public Parent {
        int n;

    public:
        void show() {
        }
    };
}

// int main() {
//     using namespace vir;
//     cout << sizeof(Parent) << endl;
//     cout << sizeof(Child) << endl;
//     return 0;
// }

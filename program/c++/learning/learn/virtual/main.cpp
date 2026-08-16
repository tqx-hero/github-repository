//
// Created by Administrator on 2026/7/15.
//
#include <iostream>
using namespace std;

class Parent {
    int num;

public:
    Parent() : num(10) {
    }
    virtual  ~Parent(){}
    virtual void print() {
        cout << "父类打印函数" << endl;
    }
};

class Child : public Parent {
public:
    void print() override{
        cout << "子类打印函数" << endl;
    }
};

void print(Parent *parent) {
    parent->print();
}

// int main() {
//     // Parent *pp = new Child;
//     // print(pp);
//     // delete pp;
//
//     Parent pt;
//     Child ch;
//     cout << sizeof(pt) << endl;
//     cout << sizeof(ch) << endl;
//     //用指针手动绑定虚表
//     long long *lptr = (long long *) &pt, *cptr = (long long *) &ch;
//     *lptr = *cptr;
//     print(&pt);
//     return 0;
// }

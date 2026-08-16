//
// Created by Administrator on 2026/7/15.
//
#include <iostream>
using namespace std;

class Parent {
public:
    Parent() {
        cout << "调用父类构造函数" << endl;
        //子类构造器构造之前需要先构造父类，此时的vptr指针指向的是父类所在的只读虚表
        //调用该方法为虚函数，即可重写函数，编译器会根据vptr指向的虚表查找该函数进行调用
        //所以执行的是父类的虚函数
        // print();
    };

    virtual void print() {
        cout << "调用父类打印函数" << endl;
    }
     void printt() {
        cout << "调用父类打印函数" << endl;
    }
};

class Child : public Parent {
public:
    Child() : Parent() {
        //父类初始化完毕后，因为需要构建子类虚表，虚表指针vptr不再指向父类的只读虚表，会指向子类的虚表
        //此时调用print函数，会从子类找到该虚函数
        //注意：必须是虚函数，即可重写的函数，如果是非虚函数，就先从子类中找，找到了调用，没找到去父类找
        printt();
    };

    void print() override {
        cout << "调用子类打印函数" << endl;
    }
    void printt()  {
        cout << "调用子类打印函数" << endl;
    }
};


// int main() {
//     Child ch;
//     return 0;
// }

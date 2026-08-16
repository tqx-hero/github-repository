//
// Created by Administrator on 2026/7/13.
//
#include <iostream>
using namespace std;

class Parent {
    int pri;

public:
    int pub;

protected:
    int pro;
};

//公有继承方式：public修饰
class Child : public Parent {
public:
    void print() {
        cout << pro << endl;
        cout << pub << endl; //公有成员变量与protected类型的都可以在子类访问
        // cout << pri << endl;    //私有成员变量不能访问
    }
};

//保护继承方式，父类的public成员变量变成了protected，只能在子类内部访问，不允许外部访问
//该行为只是针对外部对子类的访问权限控制，不会改变子类对父类的访问控制(这需要父类的各访问修饰符进行控制)
class Child1 : protected Parent {
public:
    void print() {
        cout << pub << endl;
        cout << pro << endl;
        // cout << pri <<endl; //继承方式的权限，只能向下兼容，即原来的私有成员变量，通过更高级的继承方式，也不能改变其私有属性
    }
};
//私有继承。会把父类的共有成员、保护成员，对外部全部表现为私有，但是子类对父类的访问权限不会改变。
class Child2 : Parent {
public:
    void print() {
        cout << pub << endl;
        cout << pro << endl;
        // cout << pri << endl;
    }
};


// int main() {
//     Child ch;
//     ch.pub; //公有继承方式下，外部可直接通过子类使用父类的public成员变量
//     // ch.pro; //公有继承，protected与private的成员变量不能直接访问
//
//     Child1 ch1;
//     // ch1.pub; //保护继承下，父类的公有成员在子类变成了protected，外部不能访问,但可以被继承
//     Child2 ch2;
//     // ch2.pub;
//     return 0;
// }

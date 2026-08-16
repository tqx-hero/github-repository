//
// Created by Administrator on 2026/7/11.
//

#include <cstring>
#include <iostream>
using namespace std;
//等号操作符重载。当类中定义指针类型的成员变量，如果不重载=运算符，那当进行=赋值时会默认调用赋值函数
//指针地址内指向的内存地址也会拷贝到左值，即完成浅拷贝，并且没有释放左值原来的指针指向的那块内存导致内存泄漏
//再就是浅拷贝的通病。两个对象指向同一块内存，当分别析构时会释放同一块内存2次，导致系统崩溃。
class A {
    int num;
    char *name;

public:
    A(int num, const char *name)
        : num(num) {
        //运用c的函数库，申请一块内存空间，拷贝到该对象name
        this->name = new char[strlen(name) + 1];
        strcpy(this->name, name);
    }

    ~A() {
        delete[] this->name;
        this->name = nullptr;
    }

    //拷贝构造，仍然是在对象进行初始化时操作的，所以可以直接设置对象的值，深拷贝即可
    A(const A &a) : num(a.num) {
        //运用c的函数库，申请一块内存空间，拷贝到该对象name
        this->name = new char[strlen(a.name) + 1];
        strcpy(this->name, a.name);
    }

    void print() {
        cout << "name :" << name << endl;
        cout << "num :" << num << endl;
    }

    //如果是赋值= ，如： a=b,a与b均是已经初始化完成的对象
    //当赋值时需要重载=。重载函数内需要干三件事情:
    //前提：判断a是否与b是同一个对象，是直接返回，不是在进行后续操作.
    //1、获取a的所有指针成员变量，依次释放内存，避免内存泄漏
    //2、开辟新的内存空间，获取新的指针，以b的指针变量指向的数据为模板进行深拷贝
    //3、给a赋值新的成员变量数据，包括深拷贝完成的指针类型与其他基本数据类型
    A &operator=(const A &a) {
        //判断是否为同一个对象，是直接返回
        if (this == &a)
            return *this;
        this->num = a.num;
        //释放原指针指向的内存
        delete[] this->name;
        //深拷贝
        this->name = new char[strlen(a.name) + 1];
        strcpy(this->name, a.name);
        return *this;
    }
};

// int main() {
//     A a(1, "张三"), b(2, "李四"), c(a);
//     a = b;
//     a.print();
//     c.print();
//     return 0;
// }

//
// Created by Administrator on 2026/7/14.
//
#include <iostream>
using namespace std;

class Parent {
public:
    //给父类添加虚函数关键字，告诉编译器这个函数不要在编译器决定它的对象类型，需要在运行时去决定
    //添加了虚函数后，子类需要对虚函数进行重写
    virtual void print() {
        cout << "调用父类的打印函数" << endl;
    }

    void get() {
        cout << "调用父类的get方法" << endl;
    }

    //对于父类，析构函数必须为虚函数，为满足多态性质，否则容易导致内存泄漏
    virtual ~Parent() {
        cout << "父类析构函数被调用" << endl;
    }
};

class Child : public Parent {
public:
    void print() override {
        cout << "调用子类的打印函数" << endl;
    }
    //由于父类的get函数不是虚函数，子类的同名函数会让父类的函数隐藏，默认调用时会调用这个函数
    //属于重定义
    void get() {
        cout << "调用子类的get方法" << endl;
    }

    ~Child() override {
        cout << "子类析构函数被调用" << endl;
    }
};

//只要最顶层超类声明的函数以及析构函数为虚函数，那它的所有子类以及子类的子类等都可以重写这些虚函数（当然析构函数的函数名必须与自身类名相同）.
//这些函数都拥有多态行为。
//如果写的类中的函数允许子类被重写，那就可以声明它为虚函数。
class Child2 : public Child {
public:
    void print() override {
        cout << "调用子类2的打印函数" << endl;
    }

    ~Child2() override {
        cout << "子类2析构函数被调用" << endl;
    }
};

void print(Parent &base) {
    base.print();
    delete &base; //如果析构函数没有声明为虚函数，那么析构函数就不会有多态，编译器会直接调用Parent类的析构函数，而不是根据运行时动态联编
    //解决办法与其他函数一样，将父类的析构函数声明成虚函数，这样子类的析构函数就相当于对父类析构的重写，编译器不再静态联编
    //而是去动态联编，产生多态性质
}

// int main() {
//     // Parent pa;
//     // Child *ch = new Child;
//     // print(pa);
//     // print(*ch);
//
//     // Child2 *ch2 = new Child2;
//     // print(*ch2);
//
//     // Child ch3;
//     // ch3.Parent::get();
//     // ch3.get();
//     return 0;
// }

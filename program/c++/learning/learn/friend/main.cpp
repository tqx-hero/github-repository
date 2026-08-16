//
// Created by Administrator on 2026/7/10.
//
#include <iostream>
using namespace std;

class Number;

class NumberB {
public:
    //因为Number为一个对象，编译器在执行到这里时由于还没加载到Number，不能确定类中有什么
    //所以不能直接写入函数体，只能在这里使用函数声明，把函数体放到Number类后面
    //就是等编译器解析完了Number类之后才能使用Number里面的成员变量，包括私有变量
    void prints(Number &number);
};

class Number {
    //友元函数，告诉编译器，被friend修饰的外部函数可以访问该类的私有变量
    friend void print(Number &number);

    //声明一个类为该类的friend，被声明的类所有函数都可访问本类的私有变量
    // friend class NumberB;
    //声明类中的某个函数为friend
    friend void NumberB::prints(Number &number);

    int num;

public:
    explicit Number(int num)
        : num(num) {
    }

    Number() : num(0) {
    };
};


void print(Number &number) {
    cout << number.num << endl;
}

void NumberB::prints(Number &number) {
    cout << number.num << endl;
}

// int main() {
//     return 0;
// }

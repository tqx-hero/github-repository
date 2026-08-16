//
// Created by Administrator on 2026/7/3.
//

#include "Child.h"

#include <iostream>

Child::Child() : Parent(10) {
    std::cout << "child is &p = " << this << std::endl;
}

void Child::modify(int c) {
    //父类的私有变量不允许子类去直接访问，只能通过父类的函数去操作
    // count = c;
    set(c);
    print();
}

Child::~Child() {
    std::cout << "child 析构函数" << std::endl;
}

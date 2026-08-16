//
// Created by Administrator on 2026/7/3.
//

#include "Parent.h"
#include <iostream>
using namespace std;

Parent::Parent() : count(0) {
    cout << "parent is &p = " << this << endl;
}

Parent::~Parent() {
    std::cout << "parent 析构函数" << std::endl;
}

Parent::Parent(int count) : count(count) {
}

void Parent::set(int count) {
    this->count = count;
}

void Parent::print() {
    cout << "print is &p = " << this << endl;
    cout << "count = " << this->count << endl;
}

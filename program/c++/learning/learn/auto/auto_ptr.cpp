//
// Created by Administrator on 2026/7/12.
//
//智能指针
#include "auto_ptr.h"

#include <iostream>
#include <memory>
using namespace std;

ABC::ABC() : num(0) {
}

void ABC::set_num(int num) {
    this->num = num;
}

int ABC::get_num() {
    return this->num;
}

ABC::ABC(int num)
    : num(num) {
}

MyAutoPtr::MyAutoPtr(ABC *a) {
    a_ptr = a;
}

MyAutoPtr::~MyAutoPtr() {
    delete a_ptr;
    a_ptr = nullptr;
}

//重载解引用运算符,返回智能指针包裹的对象本身
ABC &MyAutoPtr::operator*() {
    return *this->a_ptr;
}

//重载指针运算符 ->,返回智能指针包裹对象的指针
ABC *MyAutoPtr::operator->() {
    return this->a_ptr;
}

// int main() {
//     // unique_ptr<int> uip(int);
//     MyAutoPtr map(new ABC);
//     (*map).set_num(20);
//     cout << (*map).get_num() << endl;
//     map->set_num(30);
//     cout << map->get_num() << endl;
//     return 0;
// }

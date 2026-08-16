//
// Created by Administrator on 2026/7/12.
//

#ifndef LN_AUTO_PTR_H
#define LN_AUTO_PTR_H

class ABC {
    int num;

public:
    ABC();

    void set_num(int num);

    int get_num();

    ABC(int num);
};

//手写智能指针
class MyAutoPtr {
    ABC *a_ptr;

public:
    MyAutoPtr(ABC *a);

    ~MyAutoPtr();

    //重载解引用运算符,返回智能指针包裹的对象本身
    ABC &operator*();

    //重载指针运算符 ->,返回智能指针包裹对象的指针
    ABC *operator->();
};
#endif //LN_AUTO_PTR_H

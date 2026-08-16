//
// Created by Administrator on 2026/7/3.
//

#ifndef LN_PARENT_H
#define LN_PARENT_H


class Parent {
    //私有变量不能被继承，子类同样也不能直接访问，只能通过父类的相关函数进行操作
    int count;

public:
    Parent();

     Parent(int count);

    ~Parent();

    void set(int count);

    void print();
};


#endif //LN_PARENT_H

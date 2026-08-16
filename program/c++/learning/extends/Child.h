//
// Created by Administrator on 2026/7/3.
//

#ifndef LN_CHILD_H
#define LN_CHILD_H
#include "Parent.h"


class Child : public Parent{
public:
    Child();
    void modify(int c);

    ~Child();
};



#endif //LN_CHILD_H

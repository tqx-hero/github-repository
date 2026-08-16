//
// Created by Administrator on 2026/7/15.
//

#ifndef LN_SECURITY_H
#define LN_SECURITY_H
#include <iostream>
using namespace std;
//抽象类的面向接口编程，多态实现
class Security {
public:
    virtual void fightPeople()=0;

    virtual ~Security(){};
};

#endif //LN_SECURITY_H

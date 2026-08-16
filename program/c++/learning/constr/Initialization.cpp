//
// Created by Administrator on 2026/7/3.
//

#include "Initialization.h"
//可以通过在函数名后面 : 变量名(变量值)的方式来初始化变量的值
//多个变量之间用,隔开。
//此种初始化变量的方法是在初始化变量时就直接将值赋值给变量。
//初始化时机早于构造函数，因为还没进入构造函数.
//如果在构造函数内进行 = 赋值，那就是先初始化完成变量以后，再进行赋值操作，在执行逻辑上
//多运行一步赋值。
Initialization::Initialization(int num, float f) : num(num), f(f) {
}
//可以通过这种方式对变量进行初始化，同时设置初始化的默认值
Initialization::Initialization() : num(0), f(0.00f) {
}

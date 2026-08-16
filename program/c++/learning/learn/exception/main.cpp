//
// Created by Administrator on 2026/7/17.
//
#include <iostream>

static inline int mDiv(int x, int y) {
    if (!y)
        throw y;
    return x / y;
}

static void test01() {
    try {
        mDiv(10, 0);
        mDiv(20, 1);
    } catch (int exec) {
        std::cout << "除数为 " << exec << std::endl;
    }
}

static void test02(int x, int y) {
    mDiv(x, y);
}
//与java不同的是：c++的异常可以跨函数，即函数调用链上：a->b->c。如果c抛出异常，b没有捕获，而a捕获了，那a也能捕获到c抛出的异常
//这点java是做不到的
static void test03() {
    try {
        test02(10, 0);
    } catch (int e) {
        std::cout << "除数为:" << e << std::endl;
    }
}

// int main() {
//     // test01();
//     test03();
//     return 0;
// }

//
// Created by Administrator on 2026/7/16.
//
#include <iostream>
template<typename T>
class Persion {
public:
   static  void set(int x) {
        num = x;
    }

   static  int get() {
        return num;
    }

private:
    static int num;
};

//初始化类模板中的静态变量
//因为是类模板，在使用时会初始化成不同的模板类
//每个模板类中都有一个num静态变量储存在静态区。
template<typename T>
int Persion<T>::num = 0;

// int main() {
//     //对于Persion<int>类，num与Persion<double>类的num不是同一个变量，因为这两个不是同一个类
//     Persion<int> p1, p2, p3;
//     p1.set(10);
//     Persion<int>::set(11);
//     std::cout << Persion<int>::get() << std::endl;
//     Persion<double> d1, d2, d3;
//     d2.set(30);
//     std::cout << d1.get() << std::endl;
//     return 0;
// }

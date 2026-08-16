#include <iostream>
#include <ostream>
//
// Created by Administrator on 2026/7/6.
//
using namespace std;

class Integer {
    int i;

public:
    Integer(int i)
        : i(i) {
        // std::cout << "i = " << i << std::endl;
    }

    Integer() : i(0) {
    }

    int get() { return this->i; }

    const Integer operator +(const Integer &in) const {
        return Integer(this->i + in.i);
    }
};

class Integer3 {
public:
    int k;
    int m;

    Integer3(int k)
        : k(k), m(0) {
    }
};

class Integer2 {
    int j;

public:
    Integer2(int j)
        : j(j) {
    }

    Integer2(Integer &i1) : j(i1.get()) {
    }

    Integer2() : j(0) {
    }

    //接受同类型的参数，进行运算
    const Integer2 operator*(const Integer2 &i2) const {
        return Integer2(this->j * i2.j);
    }

    //重载函数，接收不同类型的参数进行直接运算。
    //省去了把参数包装成Integer2对象的步骤，效率更高
    //但是通用性、可扩展性差，不能复用。
    const Integer2 operator*(const Integer3 &i3) const {
        return Integer2(this->j * i3.k);
    }

    int get() {
        return this->j;
    }
};

// int main() {
//     Integer x(10), y = {20}, z;
//     Integer2 u(100), v;
//     Integer3 w = 3;
//     //运算符重载之后，编译器会首先以运算符左侧的算子的类型作为基准，与运算符后面的算子做运算
//     //所以对象之间的运算，需要注意运算符左侧的算子所在的对象类型是否有对操作符的定义。
//     //后面的如果是其他数据类型，必须提供对应的数据类型转换函数，即需要定义x类的构造函数，用来使y的生成x类的对象
//     //结果是2者类型都变成Integer后，再利用重载的运算符+来做运算。
//     // z = x + y;
//     //操作符+左边x为Integer类型，后面3为整型。编译器会调用左边x的类Integer的构造函数，传入整型参数3来生成后面的对象
//     //使两者都变为Integer类型对象，再次利用Integer类中重载的运算符+进行运算
//     z = x + 3;
//     std::cout << "z = " << z.get() << std::endl;
//     //编译器调用Integer2的构造函数，把x转换为与u相同的数据类型，然后与其进行操作符运算
//     v = u * x;
//     std::cout << "v = " << v.get() << std::endl;
//
//     //直接调用的u的操作符重载函数，把w作为参数传入，进行直接运算，而没有先用w生成u类型的对象
//     v = u * w;
//     cout << "v*w = " << v.get() << endl;
//     return 0;
// }

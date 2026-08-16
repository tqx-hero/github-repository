//
// Created by Administrator on 2026/7/22.
//
#include <iostream>

namespace rtti {
    class A {
    public:
        virtual ~A() = default;
    };

    class B : public A {
    };
}

// int main() {
//     // using namespace std;
//     // int a,b;
//     // double c,d;
//     // double * dp = reinterpret_cast<double *>(&a);
//     // //编译阶段查询变量的数据类型
//     // cout << (typeid(a)==typeid(b)) << endl;
//     // //可通过.name来获取类型的字符串表达形式
//     // cout << (typeid(a).name()) <<endl;
//     // cout << (typeid(a) == typeid(c)) << endl;
//     // cout << (typeid(int).name()) << endl;
//     // cout << (typeid(a) == typeid(*dp)) << endl;
//     // cout << typeid(dp).name() << endl;
//     using namespace rtti;
//     using namespace std;
//     B b;
//     A *ap = &b;
//     //基类必须要有虚函数，才会产生多态，产生多态之后，typeid才会在运行时查虚表找到虚表内的typeinfo信息，读取到对象的指针数据类型
//     //如果基类没有虚函数，即使子类继承了父类，那也没有产生多态性，编译器会在编译器确定数据类型，即为基类
//     cout << typeid(*ap).name() << endl;
//     //对于指针类型，没有继承的概念(继承与多态是针对对象，指针不是对象实体)，更没有多态的概念，所以对指针求typeid，编译期即可确定其类型
//     //为 A*
//     cout << typeid(ap).name() << endl;
//     return 0;
// }

//
// Created by Administrator on 2026/7/21.
//
#include <iostream>

namespace ext {
    using namespace std;

    class Parent {
    public:
        virtual void show(int x) {
            cout << "调用父类的虚函数" << endl;
        }
    };

    class Child : public Parent {
    public:
        void show(double x) {
            cout << "调用子类的函数" << endl;
        }
    };
}

// int main() {
//     using namespace ext;
//     Child ch;
//     Parent p;
//     Parent *ptr = &ch;
//     ch.show(10); //通过子类对象直接调用函数，不是使用父类指针去访问，没有多态性，直接访问成员函数
//     ptr->show(10); //show为虚函数，具有多态性，调用父类构造函数时，创建父类的虚函数表，把父类的所有虚函数拷贝到虚表
//     //再调用自身的构造函数，同时修改自己的虚表
//     //自身类的虚函数添加到虚表中，如果有相同签名的虚函数会进行覆盖，即子类的重写函数覆盖父类
//     //不相同的则追加。该案例中是先把父类的虚函数show添加到虚表，轮到调用自己构造函数时发现自身类没有虚函数
//     //show(double)是一个成员函数，不会添加到虚表，走的是静态联编。
//     //通过父类指针调用show函数时，发现该函数(int类型参数)是虚函数，会直接查虚表，找到函数入口，入口地址为父类的虚函数
//     ch.Parent::show(10); //通过子类.父类::函数()显式调用父类的函数,否则直接使用ch.show()，会先从子类按照函数名称查找函数，找到了停止查找，找不到再去父类查找
//     //如果子类中找到了同名函数但参数列表不匹配时，同样不会向上查找，编译器会直接报错。
//     return 0;
// }

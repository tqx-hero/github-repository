//
// Created by Administrator on 2026/7/15.
//
//抽象类定义：如果一个类中有纯虚函数，那么这个类就是抽象类，不能被实例化。
#include <iostream>
using namespace std;

class Shape {
public:
    virtual double getArea() =0;

    virtual ~Shape() {
        cout << "抽象类析构" << endl;
    }

    int a;
    int b;
};

//继承抽象类的子类必须重写抽象类的抽象方法，否则该子类也是一个抽象类
class Rect : public Shape {
public:
    double getArea() override {
        cout << "正方形面积..." << endl;
        return 0.0f;
    }

    ~Rect() override {
        cout << "子类析构函数..." << endl;
    }

    void print() {
    }
};

// int main() {
//     Shape *sh = new Rect;
//     sh->getArea();
//     delete sh;
//     return 0;
// }

//
// Created by Administrator on 2026/7/14.
//
#include <iostream>
using namespace std;

class Furniture {
public:
    int m;
};

//通过在子类添加virtual，以虚继承的方式继承父类，这样在这个类作为父类被其他子类多继承时，如果遇到多个同样的变量，消除歧义
class Sofa : virtual public Furniture {
public:
    void sit() {
        cout << "在沙发上坐" << endl;
    }
};

class Bed : virtual public Furniture {
public:
    void sleep() {
        cout << "在床上睡觉" << endl;
    }
};

class SofaBed : public Sofa, public Bed {
public:
    void slAndSet() {
        // m = 10; //家具类的m由于有2个子类都继承，且沙发床类又多继承了这2个子类，当前访问该变量时，编译器不知道要使用哪个m，产生二义性
        Sofa::m = 20; //解决方法是使用作用域解析符，指明变量的作用域，消除二义性
        Bed::m = 30;
        sit();
        sleep();
    }
};

// int main() {
//     SofaBed sf;
//     sf.slAndSet();
//     // sf.Bed::m = 20; //在外部访问也必须声明作用域，指明调用的哪个变量。注意继承方式一定要是公有继承，并且变量m为public，可供外部访问
//     // sf.Sofa::m = 30;
//     sf.m = 10;
//     return 0;
// }

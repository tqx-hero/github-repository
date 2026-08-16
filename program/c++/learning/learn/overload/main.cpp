//
// Created by Administrator on 2026/7/9.
//
#include <iostream>
using namespace std;
#if 0
void f(int x) {
    cout << "x : " << x << endl;
}

void f(double x) {
    cout << "d : " << x << endl;
}

void f(string x) {
    cout << "string : " << x << endl;
}
#endif

const string &getStr(const string name, int x, double y) {
    cout << "name : " << name << endl;
    cout << "age : " << x << endl;
    cout << "score : " << y << endl;
    return name;
}

//或者可以声明一个函数类型的类型,编译器会对该函数类型自动添加指针类型
typedef const string &fc(const string, int, double);

// void print(const string name, int x, double y, fc func) {
//     func(name, x, y);
// }

//可以将函数指针定义成一个类型，使代码更有可读性
typedef const string & (*fuc)(const string, int, double);

// void print(const string name, int x, double y, fuc func) {
//     func(name, x, y);
// }

//可以使用c++11新增的运算符decltype，自动推断函数类型，不需要再用以上的c的方法自动写入，编译器自动推断
typedef decltype(getStr) fcc;

// void print(const string name, int x, double y, fcc func) {
//     func(name, x, y);
// }

//或者写成这种形式，即指针形式，表达更规范
typedef decltype(getStr) *fcp;

// void print(const string name, int x, double y, fcp func) {
//     func(name,x,y);
// }

//下面2个函数，编译器会对没有指针类型的那个函数进行自动推断，然后转换成为函数指针类型的参数，所以最终结果是，这两个函数等价
void print(const string name, int x, double y, const string &(*func)(const string, int, double)) {
    func(name, x, y);
}

// void print(const string name, int x, double y, const string &func(const string, int, double)) {
//     func(name, x, y);
// }

// int main() {
//     //如果在函数内部声明外部函数，按照就近原则，后面的调用都会以该声明为准，所以如果只有
//     //这一个声明而没有对字符串参数的声明，传入字符串类型的那个函数会因为找不到字符串作为形参的函数而报错
//     // void f(double x);
//     // //再添加上对函数的声明，string类型作为参数的那个函数就可以使用了
//     // void f(string s);
//     //
//     // f(10);
//     // f(10.f);
//     // f("hello");
//
//
//     //定义函数指针,同时初始化函数
//     const string & (*funcp)(const string, int, double)(getStr);
//     //或者直接定义函数，编译器会自动推断并添加指针类型
//
//     // funcp = getStr;
//     // funcp("张三", 18, 20);
//     //运用函数指针进行动态绑定调用的函数
//     print("张三", 18, 20.1f, getStr);
//
//     return 0;
// }
